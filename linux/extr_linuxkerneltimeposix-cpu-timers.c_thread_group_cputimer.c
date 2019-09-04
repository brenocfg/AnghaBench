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
struct thread_group_cputimer {int /*<<< orphan*/  cputime_atomic; int /*<<< orphan*/  running; } ;
struct task_struct {TYPE_1__* signal; } ;
struct task_cputime {int dummy; } ;
struct TYPE_2__ {struct thread_group_cputimer cputimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sample_cputime_atomic (struct task_cputime*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_group_cputime (struct task_struct*,struct task_cputime*) ; 
 int /*<<< orphan*/  update_gt_cputime (int /*<<< orphan*/ *,struct task_cputime*) ; 

void thread_group_cputimer(struct task_struct *tsk, struct task_cputime *times)
{
	struct thread_group_cputimer *cputimer = &tsk->signal->cputimer;
	struct task_cputime sum;

	/* Check if cputimer isn't running. This is accessed without locking. */
	if (!READ_ONCE(cputimer->running)) {
		/*
		 * The POSIX timer interface allows for absolute time expiry
		 * values through the TIMER_ABSTIME flag, therefore we have
		 * to synchronize the timer to the clock every time we start it.
		 */
		thread_group_cputime(tsk, &sum);
		update_gt_cputime(&cputimer->cputime_atomic, &sum);

		/*
		 * We're setting cputimer->running without a lock. Ensure
		 * this only gets written to in one operation. We set
		 * running after update_gt_cputime() as a small optimization,
		 * but barriers are not required because update_gt_cputime()
		 * can handle concurrent updates.
		 */
		WRITE_ONCE(cputimer->running, true);
	}
	sample_cputime_atomic(times, &cputimer->cputime_atomic);
}