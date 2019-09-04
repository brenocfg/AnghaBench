#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct sighand_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  entry; scalar_t__ firing; struct task_struct* task; } ;
struct TYPE_4__ {TYPE_1__ cpu; } ;
struct k_itimer {TYPE_2__ it; } ;

/* Variables and functions */
 int TIMER_RETRY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct sighand_struct* lock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static int posix_cpu_timer_del(struct k_itimer *timer)
{
	int ret = 0;
	unsigned long flags;
	struct sighand_struct *sighand;
	struct task_struct *p = timer->it.cpu.task;

	WARN_ON_ONCE(p == NULL);

	/*
	 * Protect against sighand release/switch in exit/exec and process/
	 * thread timer list entry concurrent read/writes.
	 */
	sighand = lock_task_sighand(p, &flags);
	if (unlikely(sighand == NULL)) {
		/*
		 * We raced with the reaping of the task.
		 * The deletion should have cleared us off the list.
		 */
		WARN_ON_ONCE(!list_empty(&timer->it.cpu.entry));
	} else {
		if (timer->it.cpu.firing)
			ret = TIMER_RETRY;
		else
			list_del(&timer->it.cpu.entry);

		unlock_task_sighand(p, &flags);
	}

	if (!ret)
		put_task_struct(p);

	return ret;
}