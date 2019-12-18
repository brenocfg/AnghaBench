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
 int /*<<< orphan*/  check_light_led (int /*<<< orphan*/ ) ; 
 int skip_led ; 

void led_set_keymap(uint8_t usb_led) {
    if (skip_led) {
        skip_led = false;
        return;  // Skip calls triggered by the Fn layer turning on
    }
    check_light_led(usb_led);
}