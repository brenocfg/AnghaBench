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
struct TYPE_2__ {int /*<<< orphan*/  raw; scalar_t__ cont; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_update_haptic (int /*<<< orphan*/ ) ; 
 TYPE_1__ haptic_config ; 
 int /*<<< orphan*/  haptic_disable_continuous () ; 
 int /*<<< orphan*/  haptic_enable_continuous () ; 

void haptic_toggle_continuous(void) {
#ifdef DRV2605L
    if (haptic_config.cont) {
        haptic_disable_continuous();
    } else {
        haptic_enable_continuous();
    }
    eeconfig_update_haptic(haptic_config.raw);
#endif
}