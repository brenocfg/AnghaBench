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
 int /*<<< orphan*/  CONFIG_LED_IO ; 
 int PORTB ; 
 int PORTD ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  led_set_user (int) ; 
 int /*<<< orphan*/  print_dec (int) ; 

void led_set_kb(uint8_t usb_led) {
    CONFIG_LED_IO;
    print_dec(usb_led);
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        PORTB &= ~(1<<7);
    else
        PORTB |=  (1<<7);

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        PORTD &= ~(1<<0);
    else
        PORTD |=  (1<<0);

    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        PORTD &= ~(1<<1);
    else
        PORTD |=  (1<<1);
	led_set_user(usb_led);
}