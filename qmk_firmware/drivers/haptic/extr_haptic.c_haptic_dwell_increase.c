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
typedef  int uint8_t ;
struct TYPE_2__ {int dwell; } ;

/* Variables and functions */
 scalar_t__ SOLENOID_MAX_DWELL ; 
 TYPE_1__ haptic_config ; 
 int /*<<< orphan*/  haptic_set_dwell (int) ; 
 int /*<<< orphan*/  solenoid_set_dwell (int) ; 

void haptic_dwell_increase(void) {
    uint8_t dwell = haptic_config.dwell + 1;
#ifdef SOLENOID_ENABLE
    if (haptic_config.dwell >= SOLENOID_MAX_DWELL) {
        dwell = 1;
    }
    solenoid_set_dwell(dwell);
#endif
    haptic_set_dwell(dwell);
}