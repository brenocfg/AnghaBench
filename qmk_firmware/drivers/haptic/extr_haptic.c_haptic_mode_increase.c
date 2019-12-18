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
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 scalar_t__ drv_effect_max ; 
 TYPE_1__ haptic_config ; 
 int /*<<< orphan*/  haptic_set_mode (int) ; 

void haptic_mode_increase(void) {
    uint8_t mode = haptic_config.mode + 1;
#ifdef DRV2605L
    if (haptic_config.mode >= drv_effect_max) {
        mode = 1;
    }
#endif
    haptic_set_mode(mode);
}