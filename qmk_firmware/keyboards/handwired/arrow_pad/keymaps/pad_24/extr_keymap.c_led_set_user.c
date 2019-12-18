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

void led_set_user(uint8_t usb_led)
{
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output high
        DDRD |= (1<<6);
        PORTD |= (1<<6);
    } else {
        // Hi-Z
        DDRD &= ~(1<<6);
        PORTD &= ~(1<<6);
    }
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // output low
        DDRC |= (1<<7);
        PORTC |= ~(1<<7);
    } else {
        // Hi-Z
        DDRC &= ~(1<<7);
        PORTC &= ~(1<<7);
    }
}