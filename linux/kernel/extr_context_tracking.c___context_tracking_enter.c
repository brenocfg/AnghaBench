#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum ctx_state { ____Placeholder_ctx_state } ctx_state ;
struct TYPE_5__ {int /*<<< orphan*/  state; int /*<<< orphan*/  active; } ;
struct TYPE_4__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int CONTEXT_USER ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 TYPE_3__ context_tracking ; 
 int /*<<< orphan*/  context_tracking_recursion_enter () ; 
 int /*<<< orphan*/  context_tracking_recursion_exit () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  rcu_user_enter () ; 
 int /*<<< orphan*/  trace_user_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtime_user_enter (TYPE_1__*) ; 

void __context_tracking_enter(enum ctx_state state)
{
	/* Kernel threads aren't supposed to go to userspace */
	WARN_ON_ONCE(!current->mm);

	if (!context_tracking_recursion_enter())
		return;

	if ( __this_cpu_read(context_tracking.state) != state) {
		if (__this_cpu_read(context_tracking.active)) {
			/*
			 * At this stage, only low level arch entry code remains and
			 * then we'll run in userspace. We can assume there won't be
			 * any RCU read-side critical section until the next call to
			 * user_exit() or rcu_irq_enter(). Let's remove RCU's dependency
			 * on the tick.
			 */
			if (state == CONTEXT_USER) {
				trace_user_enter(0);
				vtime_user_enter(current);
			}
			rcu_user_enter();
		}
		/*
		 * Even if context tracking is disabled on this CPU, because it's outside
		 * the full dynticks mask for example, we still have to keep track of the
		 * context transitions and states to prevent inconsistency on those of
		 * other CPUs.
		 * If a task triggers an exception in userspace, sleep on the exception
		 * handler and then migrate to another CPU, that new CPU must know where
		 * the exception returns by the time we call exception_exit().
		 * This information can only be provided by the previous CPU when it called
		 * exception_enter().
		 * OTOH we can spare the calls to vtime and RCU when context_tracking.active
		 * is false because we know that CPU is not tickless.
		 */
		__this_cpu_write(context_tracking.state, state);
	}
	context_tracking_recursion_exit();
}