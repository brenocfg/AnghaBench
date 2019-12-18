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
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct idle_timer {scalar_t__ done; TYPE_1__ timer; } ;
struct TYPE_5__ {scalar_t__ policy; int nr_cpus_allowed; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 unsigned long NSEC_PER_USEC ; 
 int PF_IDLE ; 
 int PF_KTHREAD ; 
 int PF_NO_SETAFFINITY ; 
 int /*<<< orphan*/  READ_ONCE (scalar_t__) ; 
 scalar_t__ SCHED_FIFO ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpuidle_use_deepest_state (int) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  do_idle () ; 
 int /*<<< orphan*/  hrtimer_init_on_stack (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idle_inject_timer_fn ; 
 int /*<<< orphan*/  ns_to_ktime (unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  preempt_fold_need_resched () ; 
 int /*<<< orphan*/  rcu_sleep_check () ; 

void play_idle(unsigned long duration_us)
{
	struct idle_timer it;

	/*
	 * Only FIFO tasks can disable the tick since they don't need the forced
	 * preemption.
	 */
	WARN_ON_ONCE(current->policy != SCHED_FIFO);
	WARN_ON_ONCE(current->nr_cpus_allowed != 1);
	WARN_ON_ONCE(!(current->flags & PF_KTHREAD));
	WARN_ON_ONCE(!(current->flags & PF_NO_SETAFFINITY));
	WARN_ON_ONCE(!duration_us);

	rcu_sleep_check();
	preempt_disable();
	current->flags |= PF_IDLE;
	cpuidle_use_deepest_state(true);

	it.done = 0;
	hrtimer_init_on_stack(&it.timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	it.timer.function = idle_inject_timer_fn;
	hrtimer_start(&it.timer, ns_to_ktime(duration_us * NSEC_PER_USEC),
		      HRTIMER_MODE_REL_PINNED);

	while (!READ_ONCE(it.done))
		do_idle();

	cpuidle_use_deepest_state(false);
	current->flags &= ~PF_IDLE;

	preempt_fold_need_resched();
	preempt_enable();
}