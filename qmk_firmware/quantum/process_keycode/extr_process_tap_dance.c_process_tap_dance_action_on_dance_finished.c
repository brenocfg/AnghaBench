#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  on_dance_finished; } ;
struct TYPE_7__ {int finished; int /*<<< orphan*/  weak_mods; int /*<<< orphan*/  oneshot_mods; } ;
struct TYPE_6__ {TYPE_1__ fn; int /*<<< orphan*/  user_data; TYPE_4__ state; } ;
typedef  TYPE_2__ qk_tap_dance_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  _process_tap_dance_action_fn (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_weak_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_keyboard_report () ; 

__attribute__((used)) static inline void process_tap_dance_action_on_dance_finished(qk_tap_dance_action_t *action) {
    if (action->state.finished) return;
    action->state.finished = true;
    add_mods(action->state.oneshot_mods);
    add_weak_mods(action->state.weak_mods);
    send_keyboard_report();
    _process_tap_dance_action_fn(&action->state, action->user_data, action->fn.on_dance_finished);
}