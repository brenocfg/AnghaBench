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
typedef  int uint8_t ;

/* Variables and functions */
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
 int /*<<< orphan*/  COM4A1 ; 
 int /*<<< orphan*/  COM4B1 ; 
 int /*<<< orphan*/  COM4C1 ; 
 int /*<<< orphan*/  COM4D1 ; 
 int /*<<< orphan*/  COM5A1 ; 
 int /*<<< orphan*/  COM5B1 ; 
 int /*<<< orphan*/  COM5C1 ; 
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

__attribute__((used)) static void turnOffPWM(uint8_t timer)
{
	switch (timer)
	{
		#if defined(TCCR1A) && defined(COM1A1)
		case TIMER1A:   cbi(TCCR1A, COM1A1);    break;
		#endif
		#if defined(TCCR1A) && defined(COM1B1)
		case TIMER1B:   cbi(TCCR1A, COM1B1);    break;
		#endif
		
		#if defined(TCCR2) && defined(COM21)
		case  TIMER2:   cbi(TCCR2, COM21);      break;
		#endif
		
		#if defined(TCCR0A) && defined(COM0A1)
		case  TIMER0A:  cbi(TCCR0A, COM0A1);    break;
		#endif
		
		#if defined(TIMER0B) && defined(COM0B1)
		case  TIMER0B:  cbi(TCCR0A, COM0B1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2A1)
		case  TIMER2A:  cbi(TCCR2A, COM2A1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2B1)
		case  TIMER2B:  cbi(TCCR2A, COM2B1);    break;
		#endif
		
		#if defined(TCCR3A) && defined(COM3A1)
		case  TIMER3A:  cbi(TCCR3A, COM3A1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3B1)
		case  TIMER3B:  cbi(TCCR3A, COM3B1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3C1)
		case  TIMER3C:  cbi(TCCR3A, COM3C1);    break;
		#endif

		#if defined(TCCR4A) && defined(COM4A1)
		case  TIMER4A:  cbi(TCCR4A, COM4A1);    break;
		#endif					
		#if defined(TCCR4A) && defined(COM4B1)
		case  TIMER4B:  cbi(TCCR4A, COM4B1);    break;
		#endif
		#if defined(TCCR4A) && defined(COM4C1)
		case  TIMER4C:  cbi(TCCR4A, COM4C1);    break;
		#endif			
		#if defined(TCCR4C) && defined(COM4D1)
		case TIMER4D:	cbi(TCCR4C, COM4D1);	break;
		#endif			
			
		#if defined(TCCR5A)
		case  TIMER5A:  cbi(TCCR5A, COM5A1);    break;
		case  TIMER5B:  cbi(TCCR5A, COM5B1);    break;
		case  TIMER5C:  cbi(TCCR5A, COM5C1);    break;
		#endif
	}
}