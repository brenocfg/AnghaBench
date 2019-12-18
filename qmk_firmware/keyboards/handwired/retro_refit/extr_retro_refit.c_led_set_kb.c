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
 int DDRC ; 
 int DDRD ; 
 int PORTC ; 
 int PORTD ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  led_set_user (int) ; 

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output low
        DDRD |= (1<<0);
        PORTD &= ~(1<<0);
    } else {
        // Hi-Z
        DDRD &= ~(1<<0);
        PORTD &= ~(1<<0);
    }
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // output low
        DDRD |= (1<<1);
        PORTD &= ~(1<<1);
    } else {
        // Hi-Z
        DDRD &= ~(1<<1);
        PORTD &= ~(1<<1);
    }
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        // output low
        DDRC |= (1<<6);
        PORTC &= ~(1<<6);
    } else {
        // Hi-Z
        DDRC &= ~(1<<6);
        PORTC &= ~(1<<6);
    }

    led_set_user(usb_led);
}