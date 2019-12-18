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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  led_t ;
struct TYPE_2__ {scalar_t__ level; scalar_t__ enable; } ;

/* Variables and functions */
 scalar_t__ BACKLIGHT_LEVELS ; 
 scalar_t__ IS_LED_OFF (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_LED_ON (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 TYPE_1__ backlight_config ; 
 int /*<<< orphan*/  backlight_set (scalar_t__) ; 
 int /*<<< orphan*/  led_set_kb (scalar_t__) ; 
 int /*<<< orphan*/  led_update_kb (int /*<<< orphan*/ ) ; 

__attribute__((weak)) void led_set(uint8_t usb_led) {
#if defined(BACKLIGHT_CAPS_LOCK) && defined(BACKLIGHT_ENABLE)
    // Use backlight as Caps Lock indicator
    uint8_t bl_toggle_lvl = 0;

    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) && !backlight_config.enable) {
        // Turning Caps Lock ON and backlight is disabled in config
        // Toggling backlight to the brightest level
        bl_toggle_lvl = BACKLIGHT_LEVELS;
    } else if (IS_LED_OFF(usb_led, USB_LED_CAPS_LOCK) && backlight_config.enable) {
        // Turning Caps Lock OFF and backlight is enabled in config
        // Toggling backlight and restoring config level
        bl_toggle_lvl = backlight_config.level;
    }

    // Set level without modify backlight_config to keep ability to restore state
    backlight_set(bl_toggle_lvl);
#endif

    led_set_kb(usb_led);
    led_update_kb((led_t)usb_led);
}