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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ IS_LAYER_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_LED_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  _FN ; 
 int /*<<< orphan*/  _FS ; 
 int /*<<< orphan*/  capslock_led_off () ; 
 int /*<<< orphan*/  capslock_led_on () ; 
 int /*<<< orphan*/  gp100_led_off () ; 
 int /*<<< orphan*/  gp100_led_on () ; 

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        capslock_led_on();
    } else {
        capslock_led_off();
    }
    if (IS_LAYER_ON(_FN) || IS_LAYER_ON(_FS)) {
        gp100_led_on();
    } else {
        gp100_led_off();
    }
}