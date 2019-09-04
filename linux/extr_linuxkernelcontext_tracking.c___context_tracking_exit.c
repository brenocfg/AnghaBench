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
typedef  enum ctx_state { ____Placeholder_ctx_state } ctx_state ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_KERNEL ; 
 int CONTEXT_USER ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ context_tracking ; 
 int /*<<< orphan*/  context_tracking_recursion_enter () ; 
 int /*<<< orphan*/  context_tracking_recursion_exit () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  rcu_user_exit () ; 
 int /*<<< orphan*/  trace_user_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtime_user_exit (int /*<<< orphan*/ ) ; 

void __context_tracking_exit(enum ctx_state state)
{
	if (!context_tracking_recursion_enter())
		return;

	if (__this_cpu_read(context_tracking.state) == state) {
		if (__this_cpu_read(context_tracking.active)) {
			/*
			 * We are going to run code that may use RCU. Inform
			 * RCU core about that (ie: we may need the tick again).
			 */
			rcu_user_exit();
			if (state == CONTEXT_USER) {
				vtime_user_exit(current);
				trace_user_exit(0);
			}
		}
		__this_cpu_write(context_tracking.state, CONTEXT_KERNEL);
	}
	context_tracking_recursion_exit();
}