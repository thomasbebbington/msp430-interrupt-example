#include <msp430.h>				

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

	P1DIR = 0x01; // set p1.0 to output direction
	P1OUT = 0x01; // set p1.0 output to 1
	P1IE = 0x08; // enable interrupt on p1.3
	P1IES = 0x08; // set p1.3 interrupt to hi/lo transition

	P2DIR = 0x20; // set p2.5 to output direction
	P2OUT = 0x20; // set p2.5 output to 1

	TACTL |= MC_0; // stop clock
	TACTL |= TASSEL_2; // set clock source to SMCLK
	TACTL |= ID_3; // set divider to 8
	TACCTL0 |= CCIE; // enable timer interrupt
	TACTL |= MC_2; // set timer to continuous up mode

	_enable_interrupt();

	LPM1; // enter low power mode 1
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
    P2OUT ^= 0x20; // toggle output on p2.5
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    P1OUT ^= 0x01; // toggle output on p1.0
    P1IFG = 0x00; // reset interrupt flag
}
