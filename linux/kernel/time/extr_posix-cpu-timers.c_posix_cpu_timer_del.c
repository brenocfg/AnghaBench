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
struct task_struct {int dummy; } ;
struct sighand_struct {int dummy; } ;
struct cpu_timer {scalar_t__ firing; int /*<<< orphan*/  node; scalar_t__ head; struct task_struct* task; } ;
struct TYPE_2__ {struct cpu_timer cpu; } ;
struct k_itimer {TYPE_1__ it; } ;

/* Variables and functions */
 int EINVAL ; 
 int TIMER_RETRY ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_timer_dequeue (struct cpu_timer*) ; 
 struct sighand_struct* lock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 scalar_t__ timerqueue_node_queued (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static int posix_cpu_timer_del(struct k_itimer *timer)
{
	struct cpu_timer *ctmr = &timer->it.cpu;
	struct task_struct *p = ctmr->task;
	struct sighand_struct *sighand;
	unsigned long flags;
	int ret = 0;

	if (WARN_ON_ONCE(!p))
		return -EINVAL;

	/*
	 * Protect against sighand release/switch in exit/exec and process/
	 * thread timer list entry concurrent read/writes.
	 */
	sighand = lock_task_sighand(p, &flags);
	if (unlikely(sighand == NULL)) {
		/*
		 * This raced with the reaping of the task. The exit cleanup
		 * should have removed this timer from the timer queue.
		 */
		WARN_ON_ONCE(ctmr->head || timerqueue_node_queued(&ctmr->node));
	} else {
		if (timer->it.cpu.firing)
			ret = TIMER_RETRY;
		else
			cpu_timer_dequeue(ctmr);

		unlock_task_sighand(p, &flags);
	}

	if (!ret)
		put_task_struct(p);

	return ret;
}