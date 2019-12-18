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
 int PORTD ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 

void led_set_kb(uint8_t usb_led) {
//    led_set_user(usb_led);
	if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // Turn numlock on
		PORTD |= (1<<2);
    } else {
        // Turn numlock off
	    PORTD &= ~(1<<2);
    }
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
		PORTD |= (1<<3);
    } else {
        // Turn capslock off
		PORTD &= ~(1<<3);
    }
	if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        // Turn scrolllock on
	    PORTD |= (1<<4);
    } else {
        // Turn scrolllock off
		PORTD &= ~(1<<4);
    }
}