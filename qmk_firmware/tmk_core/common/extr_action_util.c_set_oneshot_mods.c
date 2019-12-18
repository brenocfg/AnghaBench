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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ oneshot_mods ; 
 int /*<<< orphan*/  oneshot_mods_changed_kb (scalar_t__) ; 
 int /*<<< orphan*/  oneshot_time ; 
 int /*<<< orphan*/  timer_read () ; 

void set_oneshot_mods(uint8_t mods) {
    if (oneshot_mods != mods) {
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        oneshot_time = timer_read();
#    endif
        oneshot_mods = mods;
        oneshot_mods_changed_kb(mods);
    }
}