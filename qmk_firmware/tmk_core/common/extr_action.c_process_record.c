#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  key; int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_5__ event; } ;
typedef  TYPE_1__ keyrecord_t ;
typedef  int /*<<< orphan*/  action_t ;

/* Variables and functions */
 scalar_t__ IS_NOEVENT (TYPE_5__) ; 
 int /*<<< orphan*/  debug_action (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_layer_debug () ; 
 int /*<<< orphan*/  dprint (char*) ; 
 int /*<<< orphan*/  dprintln () ; 
 int /*<<< orphan*/  layer_debug () ; 
 int /*<<< orphan*/  process_action (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_record_quantum (TYPE_1__*) ; 
 int /*<<< orphan*/  store_or_get_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void process_record(keyrecord_t *record) {
    if (IS_NOEVENT(record->event)) {
        return;
    }

    if (!process_record_quantum(record)) return;

    action_t action = store_or_get_action(record->event.pressed, record->event.key);
    dprint("ACTION: ");
    debug_action(action);
#ifndef NO_ACTION_LAYER
    dprint(" layer_state: ");
    layer_debug();
    dprint(" default_layer_state: ");
    default_layer_debug();
#endif
    dprintln();

    process_action(record, action);
}