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
 int /*<<< orphan*/  L_FN ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  caps_light () ; 
 int /*<<< orphan*/  fn_light () ; 
 int /*<<< orphan*/  restore_light () ; 

__attribute__((used)) static void check_light_led(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        caps_light();
    } else if (IS_LAYER_ON(L_FN)) {
        fn_light();
    } else {
        restore_light();
    }
}