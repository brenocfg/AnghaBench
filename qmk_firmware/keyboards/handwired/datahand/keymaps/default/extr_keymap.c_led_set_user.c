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
 int /*<<< orphan*/  LED_CAPS_LOCK ; 
 int /*<<< orphan*/  LED_NUM_LOCK ; 
 int /*<<< orphan*/  LED_SCROLL_LOCK ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  lock_led_set (int,int /*<<< orphan*/ ) ; 

void led_set_user(uint8_t usb_led) {
  lock_led_set(usb_led & (1<<USB_LED_NUM_LOCK), LED_NUM_LOCK);
  lock_led_set(usb_led & (1<<USB_LED_CAPS_LOCK), LED_CAPS_LOCK);
  lock_led_set(usb_led & (1<<USB_LED_SCROLL_LOCK), LED_SCROLL_LOCK);
}