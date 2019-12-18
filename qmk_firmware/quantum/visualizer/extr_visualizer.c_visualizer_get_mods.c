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
 int /*<<< orphan*/  get_mods () ; 
 int /*<<< orphan*/  get_oneshot_mods () ; 
 int /*<<< orphan*/  has_oneshot_mods_timed_out () ; 

uint8_t visualizer_get_mods() {
    uint8_t mods = get_mods();

#ifndef NO_ACTION_ONESHOT
    if (!has_oneshot_mods_timed_out()) {
        mods |= get_oneshot_mods();
    }
#endif
    return mods;
}