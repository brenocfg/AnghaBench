#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {void* slock_led; void* clock_led; void* nlock_led; } ;

/* Variables and functions */
 void* IS_LED_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  USB_LED_NUM_LOCK ; 
 int /*<<< orphan*/  USB_LED_SCROLL_LOCK ; 
 scalar_t__ is_keyboard_master () ; 
 int /*<<< orphan*/  led_set_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_toggle (int,void*) ; 
 TYPE_1__ serial_m2s_buffer ; 

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
	
	if (is_keyboard_master()) {
	
		serial_m2s_buffer.nlock_led = IS_LED_ON(usb_led, USB_LED_NUM_LOCK);
		serial_m2s_buffer.clock_led = IS_LED_ON(usb_led, USB_LED_CAPS_LOCK);
		serial_m2s_buffer.slock_led = IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK);

		led_toggle(3, IS_LED_ON(usb_led, USB_LED_NUM_LOCK));
		led_toggle(4, IS_LED_ON(usb_led, USB_LED_CAPS_LOCK));
		led_toggle(5, IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK));
		
	}

	led_set_user(usb_led);
}