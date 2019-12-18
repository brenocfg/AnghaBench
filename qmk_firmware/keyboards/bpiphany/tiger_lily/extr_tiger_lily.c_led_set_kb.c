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
 int DDRC ; 
 int PORTB ; 
 int PORTC ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  led_set_user (int) ; 
 int /*<<< orphan*/  print_dec (int) ; 

void led_set_kb(uint8_t usb_led) {
    DDRB |= (1<<7);
    DDRC |= (1<<5) | (1<<6);

    print_dec(usb_led);

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        PORTC &= ~(1<<5);
    else
        PORTC |=  (1<<5);

    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        PORTB &= ~(1<<7);
    else
        PORTB |=  (1<<7);

    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        PORTC &= ~(1<<6);
    else
        PORTC |=  (1<<6);

    led_set_user(usb_led);
}