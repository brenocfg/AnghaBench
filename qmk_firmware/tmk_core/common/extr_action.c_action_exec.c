#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ keyrecord_t ;
typedef  int /*<<< orphan*/  keyevent_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAUXCLICKY_ACTION_PRESS ; 
 int /*<<< orphan*/  FAUXCLICKY_ACTION_RELEASE ; 
 int /*<<< orphan*/  IS_NOEVENT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_PRESSED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_RELEASED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ONESHOT_OTHER_KEY_PRESSED ; 
 int /*<<< orphan*/  action_tapping_process (TYPE_1__) ; 
 int /*<<< orphan*/  clear_oneshot_layer_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_oneshot_mods () ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_record (TYPE_1__) ; 
 int /*<<< orphan*/  dprint (char*) ; 
 int /*<<< orphan*/  dprintln () ; 
 int /*<<< orphan*/  fauxclicky_check () ; 
 scalar_t__ has_oneshot_layer_timed_out () ; 
 scalar_t__ has_oneshot_mods_timed_out () ; 
 int /*<<< orphan*/  process_hand_swap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_record (TYPE_1__*) ; 
 int /*<<< orphan*/  retro_tapping_counter ; 

void action_exec(keyevent_t event) {
    if (!IS_NOEVENT(event)) {
        dprint("\n---- action_exec: start -----\n");
        dprint("EVENT: ");
        debug_event(event);
        dprintln();
#ifdef RETRO_TAPPING
        retro_tapping_counter++;
#endif
    }

#ifdef FAUXCLICKY_ENABLE
    if (IS_PRESSED(event)) {
        FAUXCLICKY_ACTION_PRESS;
    }
    if (IS_RELEASED(event)) {
        FAUXCLICKY_ACTION_RELEASE;
    }
    fauxclicky_check();
#endif

#ifdef SWAP_HANDS_ENABLE
    if (!IS_NOEVENT(event)) {
        process_hand_swap(&event);
    }
#endif

    keyrecord_t record = {.event = event};

#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    if (has_oneshot_layer_timed_out()) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
    }
    if (has_oneshot_mods_timed_out()) {
        clear_oneshot_mods();
    }
#endif

#ifndef NO_ACTION_TAPPING
    action_tapping_process(record);
#else
    process_record(&record);
    if (!IS_NOEVENT(record.event)) {
        dprint("processed: ");
        debug_record(record);
        dprintln();
    }
#endif
}