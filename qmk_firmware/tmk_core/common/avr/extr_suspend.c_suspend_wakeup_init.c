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

/* Variables and functions */
 int /*<<< orphan*/  backlight_init () ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  host_keyboard_leds () ; 
 int is_suspended ; 
 int /*<<< orphan*/  led_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_enable_noeeprom () ; 
 scalar_t__ rgblight_enabled ; 
 int /*<<< orphan*/  rgblight_timer_enable () ; 
 int /*<<< orphan*/  suspend_wakeup_init_kb () ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void suspend_wakeup_init(void) {
    // clear keyboard state
    clear_keyboard();
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif
    led_set(host_keyboard_leds());
#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
    is_suspended = false;
    if (rgblight_enabled) {
#    ifdef BOOTLOADER_TEENSY
        wait_ms(10);
#    endif
        rgblight_enable_noeeprom();
    }
#    ifdef RGBLIGHT_ANIMATIONS
    rgblight_timer_enable();
#    endif
#endif
    suspend_wakeup_init_kb();
}