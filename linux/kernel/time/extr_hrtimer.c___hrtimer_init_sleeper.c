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
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct hrtimer_sleeper {int /*<<< orphan*/  task; TYPE_1__ timer; } ;
typedef  enum hrtimer_mode { ____Placeholder_hrtimer_mode } hrtimer_mode ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PREEMPT_RT ; 
 int HRTIMER_MODE_HARD ; 
 int HRTIMER_MODE_SOFT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  hrtimer_wakeup ; 
 scalar_t__ task_is_realtime (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __hrtimer_init_sleeper(struct hrtimer_sleeper *sl,
				   clockid_t clock_id, enum hrtimer_mode mode)
{
	/*
	 * On PREEMPT_RT enabled kernels hrtimers which are not explicitely
	 * marked for hard interrupt expiry mode are moved into soft
	 * interrupt context either for latency reasons or because the
	 * hrtimer callback takes regular spinlocks or invokes other
	 * functions which are not suitable for hard interrupt context on
	 * PREEMPT_RT.
	 *
	 * The hrtimer_sleeper callback is RT compatible in hard interrupt
	 * context, but there is a latency concern: Untrusted userspace can
	 * spawn many threads which arm timers for the same expiry time on
	 * the same CPU. That causes a latency spike due to the wakeup of
	 * a gazillion threads.
	 *
	 * OTOH, priviledged real-time user space applications rely on the
	 * low latency of hard interrupt wakeups. If the current task is in
	 * a real-time scheduling class, mark the mode for hard interrupt
	 * expiry.
	 */
	if (IS_ENABLED(CONFIG_PREEMPT_RT)) {
		if (task_is_realtime(current) && !(mode & HRTIMER_MODE_SOFT))
			mode |= HRTIMER_MODE_HARD;
	}

	__hrtimer_init(&sl->timer, clock_id, mode);
	sl->timer.function = hrtimer_wakeup;
	sl->task = current;
}