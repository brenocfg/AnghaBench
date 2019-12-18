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

/* Variables and functions */
 int PINB ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int PORTE ; 

void set_led_state(int ledId, bool state) {
	if(state) {
		switch(ledId) {
			/* LED 0 to 5 are the leds of each keyswitch. From left to right, top to bottom. These are equal to the numbers in the legends of the default keycaps. */
			case 0:
				PORTD |= (1<<7);
				break;
			case 1:
				if((PINB & (1 << 7)) != 0) {
					PORTC |= (1<<6);
				} else {
					PORTC |= (1<<7);
				}
				break;
			case 2:
				PORTD |= (1<<4);
				break;
			case 3:
				PORTE |= (1<<6);
				break;
			case 4:
				PORTB |= (1<<4);
				break;
			case 5:
				PORTD |= (1<<6);
				break;
				/* LED 6 to 8 are the three layer leds in front of the device from left to right. */
			case 6:
				PORTD &= ~(1<<5);
				break;
			case 7:
				PORTB |= (1<<6);
				break;
			case 8:
				PORTB &= ~(1<<0);
				break;
		}
	} else {
		switch(ledId) {
			case 0:
				PORTD &= ~(1<<7);
				break;
			case 1:
				if((PINB & (1 << 7)) != 0) {
					PORTC &= ~(1<<6);
				} else {
					PORTC &= ~(1<<7);
				}
				break;
			case 2:
				PORTD &= ~(1<<4);
				break;
			case 3:
				PORTE &= ~(1<<6);
				break;
			case 4:
				PORTB &= ~(1<<4);
				break;
			case 5:
				PORTD &= ~(1<<6);
				break;
			case 6:
				PORTD |= (1<<5);
				break;
			case 7:
				PORTB &= ~(1<<6);
				break;
			case 8:
				PORTB |= (1<<0);
				break;
		}
	}
}