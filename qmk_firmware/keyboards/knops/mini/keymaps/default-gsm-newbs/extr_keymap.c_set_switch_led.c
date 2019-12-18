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

void set_switch_led(int ledId, bool state) {
	if(state) {
		switch(ledId) {
			case 1:
				PORTD |= (1<<7);
				break;
			case 2:
				if((PINB & (1 << 7)) != 0) {
					PORTC |= (1<<6);
				} else {
					PORTC |= (1<<7);
				}
				break;
			case 3:
				PORTD |= (1<<4);
				break;
			case 4:
				PORTE |= (1<<6);
				break;
			case 5:
				PORTB |= (1<<4);
				break;
			case 6:
				PORTD |= (1<<6);
				break;
		}
	} else {
		switch(ledId) {
			case 1:
				PORTD &= ~(1<<7);
				break;
			case 2:
				if((PINB & (1 << 7)) != 0) {
					PORTC &= ~(1<<6);
				} else {
					PORTC &= ~(1<<7);
				}
				break;
			case 3:
				PORTD &= ~(1<<4);
				break;
			case 4:
				PORTE &= ~(1<<6);
				break;
			case 5:
				PORTB &= ~(1<<4);
				break;
			case 6:
				PORTD &= ~(1<<6);
				break;
		}
	}
}