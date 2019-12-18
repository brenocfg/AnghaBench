#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_11__ {scalar_t__ keycode; int interrupted; scalar_t__ interrupting_keycode; scalar_t__ count; } ;
struct TYPE_9__ {TYPE_5__ state; } ;
typedef  TYPE_2__ qk_tap_dance_action_t ;
struct TYPE_8__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_10__ {TYPE_1__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int highest_td ; 
 scalar_t__ last_td ; 
 int /*<<< orphan*/  process_tap_dance_action_on_dance_finished (TYPE_2__*) ; 
 int /*<<< orphan*/  reset_tap_dance (TYPE_5__*) ; 
 TYPE_2__* tap_dance_actions ; 

void preprocess_tap_dance(uint16_t keycode, keyrecord_t *record) {
    qk_tap_dance_action_t *action;

    if (!record->event.pressed) return;

    if (highest_td == -1) return;

    for (int i = 0; i <= highest_td; i++) {
        action = &tap_dance_actions[i];
        if (action->state.count) {
            if (keycode == action->state.keycode && keycode == last_td) continue;
            action->state.interrupted          = true;
            action->state.interrupting_keycode = keycode;
            process_tap_dance_action_on_dance_finished(action);
            reset_tap_dance(&action->state);
        }
    }
}