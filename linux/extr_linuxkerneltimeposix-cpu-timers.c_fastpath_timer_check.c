#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ dl_overrun; } ;
struct TYPE_4__ {int /*<<< orphan*/  sum_exec_runtime; } ;
struct task_struct {TYPE_3__ dl; struct signal_struct* signal; int /*<<< orphan*/  cputime_expires; TYPE_1__ se; } ;
struct task_cputime {int /*<<< orphan*/  sum_exec_runtime; int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; } ;
struct TYPE_5__ {int /*<<< orphan*/  cputime_atomic; int /*<<< orphan*/  checking_timer; int /*<<< orphan*/  running; } ;
struct signal_struct {int /*<<< orphan*/  cputime_expires; TYPE_2__ cputimer; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ dl_task (struct task_struct*) ; 
 int /*<<< orphan*/  sample_cputime_atomic (struct task_cputime*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_cputime (struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ task_cputime_expired (struct task_cputime*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_cputime_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int fastpath_timer_check(struct task_struct *tsk)
{
	struct signal_struct *sig;

	if (!task_cputime_zero(&tsk->cputime_expires)) {
		struct task_cputime task_sample;

		task_cputime(tsk, &task_sample.utime, &task_sample.stime);
		task_sample.sum_exec_runtime = tsk->se.sum_exec_runtime;
		if (task_cputime_expired(&task_sample, &tsk->cputime_expires))
			return 1;
	}

	sig = tsk->signal;
	/*
	 * Check if thread group timers expired when the cputimer is
	 * running and no other thread in the group is already checking
	 * for thread group cputimers. These fields are read without the
	 * sighand lock. However, this is fine because this is meant to
	 * be a fastpath heuristic to determine whether we should try to
	 * acquire the sighand lock to check/handle timers.
	 *
	 * In the worst case scenario, if 'running' or 'checking_timer' gets
	 * set but the current thread doesn't see the change yet, we'll wait
	 * until the next thread in the group gets a scheduler interrupt to
	 * handle the timer. This isn't an issue in practice because these
	 * types of delays with signals actually getting sent are expected.
	 */
	if (READ_ONCE(sig->cputimer.running) &&
	    !READ_ONCE(sig->cputimer.checking_timer)) {
		struct task_cputime group_sample;

		sample_cputime_atomic(&group_sample, &sig->cputimer.cputime_atomic);

		if (task_cputime_expired(&group_sample, &sig->cputime_expires))
			return 1;
	}

	if (dl_task(tsk) && tsk->dl.dl_overrun)
		return 1;

	return 0;
}