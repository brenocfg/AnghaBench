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
 int DDRB ; 
 int PORTB ; 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  led_set_user (int) ; 

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
	DDRB |= (1<<6);
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
			// output low
			DDRB |= (1<<2);
			PORTB &= ~(1<<2);
		} else {
			// Hi-Z
			DDRB &= ~(1<<2);
			PORTB &= ~(1<<2);
		}
	// DDRB |= (1<<7);
	// DDRB |= (1<<1);
	// DDRB |= (1<<3);
	// DDRE |= (1<<6);
	if (usb_led == 0){
		PORTB |= (1<<6);
		// PORTB |= (1<<7);
		// PORTB |= (1<<1);
		// PORTB |= (1<<3);
		// PORTE |= (1<<6);
	}
	else{
		PORTB &= ~(1<<6);
		// PORTB &= ~(1<<7);
	}
    
	led_set_user(usb_led);
}