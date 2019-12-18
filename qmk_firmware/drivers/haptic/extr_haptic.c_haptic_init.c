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
struct TYPE_2__ {int mode; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_init () ; 
 int debug_enable ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  eeconfig_debug_haptic () ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeconfig_read_haptic () ; 
 TYPE_1__ haptic_config ; 
 int /*<<< orphan*/  haptic_reset () ; 
 int /*<<< orphan*/  solenoid_setup () ; 

void haptic_init(void) {
    debug_enable = 1;  // Debug is ON!
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    haptic_config.raw = eeconfig_read_haptic();
    if (haptic_config.mode < 1) {
        haptic_config.mode = 1;
    }
    if (!haptic_config.mode) {
        dprintf("No haptic config found in eeprom, setting default configs\n");
        haptic_reset();
    }
#ifdef SOLENOID_ENABLE
    solenoid_setup();
    dprintf("Solenoid driver initialized\n");
#endif
#ifdef DRV2605L
    DRV_init();
    dprintf("DRV2605 driver initialized\n");
#endif
    eeconfig_debug_haptic();
}