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
struct TYPE_2__ {scalar_t__ enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGBLIGHT_SPLIT_SET_CHANGE_MODE ; 
 int /*<<< orphan*/  dprintf (char*,scalar_t__) ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int /*<<< orphan*/  rgblight_timer_disable () ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void rgblight_disable_noeeprom(void) {
    rgblight_config.enable = 0;
    dprintf("rgblight disable [NOEEPROM]: rgblight_config.enable = %u\n", rgblight_config.enable);
#ifdef RGBLIGHT_USE_TIMER
    rgblight_timer_disable();
#endif
    RGBLIGHT_SPLIT_SET_CHANGE_MODE;
    wait_ms(50);
    rgblight_set();
}