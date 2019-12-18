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
struct TYPE_2__ {scalar_t__ speed; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_update_rgblight (int /*<<< orphan*/ ) ; 
 TYPE_1__ rgblight_config ; 

void rgblight_decrease_speed(void) {
    if (rgblight_config.speed > 0) rgblight_config.speed--;
    // RGBLIGHT_SPLIT_SET_CHANGE_HSVS; // NEED??
    eeconfig_update_rgblight(rgblight_config.raw);  // EECONFIG needs to be increased to support this
}