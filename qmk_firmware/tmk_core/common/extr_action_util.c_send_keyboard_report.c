#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mods; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_oneshot_mods () ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 scalar_t__ has_anykey (TYPE_1__*) ; 
 scalar_t__ has_oneshot_mods_timed_out () ; 
 int /*<<< orphan*/  host_keyboard_send (TYPE_1__*) ; 
 TYPE_1__* keyboard_report ; 
 int macro_mods ; 
 int oneshot_mods ; 
 int real_mods ; 
 int weak_mods ; 

void send_keyboard_report(void) {
    keyboard_report->mods = real_mods;
    keyboard_report->mods |= weak_mods;
    keyboard_report->mods |= macro_mods;
#ifndef NO_ACTION_ONESHOT
    if (oneshot_mods) {
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        if (has_oneshot_mods_timed_out()) {
            dprintf("Oneshot: timeout\n");
            clear_oneshot_mods();
        }
#    endif
        keyboard_report->mods |= oneshot_mods;
        if (has_anykey(keyboard_report)) {
            clear_oneshot_mods();
        }
    }

#endif
    host_keyboard_send(keyboard_report);
}