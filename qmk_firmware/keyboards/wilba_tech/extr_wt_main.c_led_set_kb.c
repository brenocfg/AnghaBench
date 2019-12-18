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
 int /*<<< orphan*/  backlight_set_indicator_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_set_user (int /*<<< orphan*/ ) ; 

void led_set_kb(uint8_t usb_led)
{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
	backlight_set_indicator_state(usb_led);
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
	led_set_user(usb_led);
}