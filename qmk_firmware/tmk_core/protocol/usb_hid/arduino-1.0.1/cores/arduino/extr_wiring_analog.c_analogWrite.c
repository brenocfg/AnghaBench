#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  COM00 ; 
 int /*<<< orphan*/  COM0A1 ; 
 int /*<<< orphan*/  COM0B1 ; 
 int /*<<< orphan*/  COM1A1 ; 
 int /*<<< orphan*/  COM1B1 ; 
 int /*<<< orphan*/  COM21 ; 
 int /*<<< orphan*/  COM2A1 ; 
 int /*<<< orphan*/  COM2B1 ; 
 int /*<<< orphan*/  COM3A1 ; 
 int /*<<< orphan*/  COM3B1 ; 
 int /*<<< orphan*/  COM3C1 ; 
 int /*<<< orphan*/  COM4A0 ; 
 int /*<<< orphan*/  COM4A1 ; 
 int /*<<< orphan*/  COM4B1 ; 
 int /*<<< orphan*/  COM4C1 ; 
 int /*<<< orphan*/  COM4D0 ; 
 int /*<<< orphan*/  COM4D1 ; 
 int /*<<< orphan*/  COM5A1 ; 
 int /*<<< orphan*/  COM5B1 ; 
 int /*<<< orphan*/  COM5C1 ; 
 int /*<<< orphan*/  HIGH ; 
 int /*<<< orphan*/  LOW ; 
#define  NOT_ON_TIMER 145 
 int OCR0 ; 
 int OCR0A ; 
 int OCR0B ; 
 int OCR1A ; 
 int OCR1B ; 
 int OCR2 ; 
 int OCR2A ; 
 int OCR2B ; 
 int OCR3A ; 
 int OCR3B ; 
 int OCR3C ; 
 int OCR4A ; 
 int OCR4B ; 
 int OCR4C ; 
 int OCR4D ; 
 int OCR5A ; 
 int OCR5B ; 
 int OCR5C ; 
 int /*<<< orphan*/  OUTPUT ; 
 int /*<<< orphan*/  TCCR0 ; 
 int /*<<< orphan*/  TCCR0A ; 
 int /*<<< orphan*/  TCCR1A ; 
 int /*<<< orphan*/  TCCR2 ; 
 int /*<<< orphan*/  TCCR2A ; 
 int /*<<< orphan*/  TCCR3A ; 
 int /*<<< orphan*/  TCCR4A ; 
 int /*<<< orphan*/  TCCR4C ; 
 int /*<<< orphan*/  TCCR5A ; 
#define  TIMER0A 144 
#define  TIMER0B 143 
#define  TIMER1A 142 
#define  TIMER1B 141 
#define  TIMER2 140 
#define  TIMER2A 139 
#define  TIMER2B 138 
#define  TIMER3A 137 
#define  TIMER3B 136 
#define  TIMER3C 135 
#define  TIMER4A 134 
#define  TIMER4B 133 
#define  TIMER4C 132 
#define  TIMER4D 131 
#define  TIMER5A 130 
#define  TIMER5B 129 
#define  TIMER5C 128 
 int /*<<< orphan*/  cbi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int digitalPinToTimer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digitalWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void analogWrite(uint8_t pin, int val)
{
	// We need to make sure the PWM output is enabled for those pins
	// that support it, as we turn it off when digitally reading or
	// writing with them.  Also, make sure the pin is in output mode
	// for consistenty with Wiring, which doesn't require a pinMode
	// call for the analog output pins.
	pinMode(pin, OUTPUT);
	if (val == 0)
	{
		digitalWrite(pin, LOW);
	}
	else if (val == 255)
	{
		digitalWrite(pin, HIGH);
	}
	else
	{
		switch(digitalPinToTimer(pin))
		{
			// XXX fix needed for atmega8
			#if defined(TCCR0) && defined(COM00) && !defined(__AVR_ATmega8__)
			case TIMER0A:
				// connect pwm to pin on timer 0
				sbi(TCCR0, COM00);
				OCR0 = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR0A) && defined(COM0A1)
			case TIMER0A:
				// connect pwm to pin on timer 0, channel A
				sbi(TCCR0A, COM0A1);
				OCR0A = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR0A) && defined(COM0B1)
			case TIMER0B:
				// connect pwm to pin on timer 0, channel B
				sbi(TCCR0A, COM0B1);
				OCR0B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR1A) && defined(COM1A1)
			case TIMER1A:
				// connect pwm to pin on timer 1, channel A
				sbi(TCCR1A, COM1A1);
				OCR1A = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR1A) && defined(COM1B1)
			case TIMER1B:
				// connect pwm to pin on timer 1, channel B
				sbi(TCCR1A, COM1B1);
				OCR1B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR2) && defined(COM21)
			case TIMER2:
				// connect pwm to pin on timer 2
				sbi(TCCR2, COM21);
				OCR2 = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR2A) && defined(COM2A1)
			case TIMER2A:
				// connect pwm to pin on timer 2, channel A
				sbi(TCCR2A, COM2A1);
				OCR2A = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR2A) && defined(COM2B1)
			case TIMER2B:
				// connect pwm to pin on timer 2, channel B
				sbi(TCCR2A, COM2B1);
				OCR2B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR3A) && defined(COM3A1)
			case TIMER3A:
				// connect pwm to pin on timer 3, channel A
				sbi(TCCR3A, COM3A1);
				OCR3A = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR3A) && defined(COM3B1)
			case TIMER3B:
				// connect pwm to pin on timer 3, channel B
				sbi(TCCR3A, COM3B1);
				OCR3B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR3A) && defined(COM3C1)
			case TIMER3C:
				// connect pwm to pin on timer 3, channel C
				sbi(TCCR3A, COM3C1);
				OCR3C = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR4A)
			case TIMER4A:
				//connect pwm to pin on timer 4, channel A
				sbi(TCCR4A, COM4A1);
				#if defined(COM4A0)		// only used on 32U4
				cbi(TCCR4A, COM4A0);
				#endif
				OCR4A = val;	// set pwm duty
				break;
			#endif
			
			#if defined(TCCR4A) && defined(COM4B1)
			case TIMER4B:
				// connect pwm to pin on timer 4, channel B
				sbi(TCCR4A, COM4B1);
				OCR4B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR4A) && defined(COM4C1)
			case TIMER4C:
				// connect pwm to pin on timer 4, channel C
				sbi(TCCR4A, COM4C1);
				OCR4C = val; // set pwm duty
				break;
			#endif
				
			#if defined(TCCR4C) && defined(COM4D1)
			case TIMER4D:				
				// connect pwm to pin on timer 4, channel D
				sbi(TCCR4C, COM4D1);
				#if defined(COM4D0)		// only used on 32U4
				cbi(TCCR4C, COM4D0);
				#endif
				OCR4D = val;	// set pwm duty
				break;
			#endif

							
			#if defined(TCCR5A) && defined(COM5A1)
			case TIMER5A:
				// connect pwm to pin on timer 5, channel A
				sbi(TCCR5A, COM5A1);
				OCR5A = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR5A) && defined(COM5B1)
			case TIMER5B:
				// connect pwm to pin on timer 5, channel B
				sbi(TCCR5A, COM5B1);
				OCR5B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR5A) && defined(COM5C1)
			case TIMER5C:
				// connect pwm to pin on timer 5, channel C
				sbi(TCCR5A, COM5C1);
				OCR5C = val; // set pwm duty
				break;
			#endif

			case NOT_ON_TIMER:
			default:
				if (val < 128) {
					digitalWrite(pin, LOW);
				} else {
					digitalWrite(pin, HIGH);
				}
		}
	}
}