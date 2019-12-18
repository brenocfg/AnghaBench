#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t keycode; int interrupted; int finished; scalar_t__ interrupting_keycode; scalar_t__ count; scalar_t__ pressed; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;
typedef  int /*<<< orphan*/  qk_tap_dance_action_t ;

/* Variables and functions */
 size_t QK_TAP_DANCE ; 
 scalar_t__ last_td ; 
 int /*<<< orphan*/  process_tap_dance_action_on_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tap_dance_actions ; 

void reset_tap_dance(qk_tap_dance_state_t *state) {
    qk_tap_dance_action_t *action;

    if (state->pressed) return;

    action = &tap_dance_actions[state->keycode - QK_TAP_DANCE];

    process_tap_dance_action_on_reset(action);

    state->count                = 0;
    state->interrupted          = false;
    state->finished             = false;
    state->interrupting_keycode = 0;
    last_td                     = 0;
}