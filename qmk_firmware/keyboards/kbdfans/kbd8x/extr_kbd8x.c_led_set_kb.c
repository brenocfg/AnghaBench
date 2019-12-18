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
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  caps_led_off () ; 
 int /*<<< orphan*/  caps_led_on () ; 
 int /*<<< orphan*/  led_set_user (int) ; 
 int /*<<< orphan*/  num_led_off () ; 
 int /*<<< orphan*/  num_led_on () ; 
 int /*<<< orphan*/  scroll_led_off () ; 
 int /*<<< orphan*/  scroll_led_on () ; 

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  if(usb_led & (1<<USB_LED_NUM_LOCK))
    {
        num_led_on();
    } else {
        num_led_off();
    }

    if(usb_led & (1<<USB_LED_CAPS_LOCK))
    {
        caps_led_on();
    } else {
        caps_led_off();
    }

    if(usb_led & (1<<USB_LED_SCROLL_LOCK))
    {
        scroll_led_on();
    } else {
        scroll_led_off();
    }

	led_set_user(usb_led);
}