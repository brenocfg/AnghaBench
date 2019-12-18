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
 int /*<<< orphan*/  clear_keys () ; 
 int /*<<< orphan*/  clear_mods () ; 
 int /*<<< orphan*/  clear_weak_mods () ; 
 int /*<<< orphan*/  host_consumer_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_system_send (int /*<<< orphan*/ ) ; 
 int is_suspended ; 
 int /*<<< orphan*/  mousekey_clear () ; 
 int /*<<< orphan*/  rgblight_enable_noeeprom () ; 
 scalar_t__ rgblight_enabled ; 
 int /*<<< orphan*/  rgblight_timer_enable () ; 
 int /*<<< orphan*/  suspend_wakeup_init_kb () ; 

void suspend_wakeup_init(void) {
    // clear keyboard state
    // need to do it manually, because we're running from ISR
    //  and clear_keyboard() calls print
    // so only clear the variables in memory
    // the reports will be sent from main.c afterwards
    // or if the PC asks for GET_REPORT
    clear_mods();
    clear_weak_mods();
    clear_keys();
#ifdef MOUSEKEY_ENABLE
    mousekey_clear();
#endif /* MOUSEKEY_ENABLE */
#ifdef EXTRAKEY_ENABLE
    host_system_send(0);
    host_consumer_send(0);
#endif /* EXTRAKEY_ENABLE */
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif /* BACKLIGHT_ENABLE */
#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
    is_suspended = false;
    if (rgblight_enabled) {
        rgblight_enable_noeeprom();
    }
#    ifdef RGBLIGHT_ANIMATIONS
    rgblight_timer_enable();
#    endif
#endif
    suspend_wakeup_init_kb();
}