#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  on_each_tap; } ;
struct TYPE_5__ {TYPE_1__ fn; int /*<<< orphan*/  user_data; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ qk_tap_dance_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  _process_tap_dance_action_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void process_tap_dance_action_on_each_tap(qk_tap_dance_action_t *action) { _process_tap_dance_action_fn(&action->state, action->user_data, action->fn.on_each_tap); }