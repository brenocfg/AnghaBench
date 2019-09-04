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
struct xfs_ail {scalar_t__ ail_target; scalar_t__ ail_target_prev; int /*<<< orphan*/  ail_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_MEMALLOC ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  freezable_schedule () ; 
 int /*<<< orphan*/  freezable_schedule_timeout (int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msecs_to_jiffies (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  xfs_ail_min (struct xfs_ail*) ; 
 long xfsaild_push (struct xfs_ail*) ; 

__attribute__((used)) static int
xfsaild(
	void		*data)
{
	struct xfs_ail	*ailp = data;
	long		tout = 0;	/* milliseconds */

	current->flags |= PF_MEMALLOC;
	set_freezable();

	while (1) {
		if (tout && tout <= 20)
			set_current_state(TASK_KILLABLE);
		else
			set_current_state(TASK_INTERRUPTIBLE);

		/*
		 * Check kthread_should_stop() after we set the task state
		 * to guarantee that we either see the stop bit and exit or
		 * the task state is reset to runnable such that it's not
		 * scheduled out indefinitely and detects the stop bit at
		 * next iteration.
		 *
		 * A memory barrier is included in above task state set to
		 * serialize again kthread_stop().
		 */
		if (kthread_should_stop()) {
			__set_current_state(TASK_RUNNING);
			break;
		}

		spin_lock(&ailp->ail_lock);

		/*
		 * Idle if the AIL is empty and we are not racing with a target
		 * update. We check the AIL after we set the task to a sleep
		 * state to guarantee that we either catch an ail_target update
		 * or that a wake_up resets the state to TASK_RUNNING.
		 * Otherwise, we run the risk of sleeping indefinitely.
		 *
		 * The barrier matches the ail_target update in xfs_ail_push().
		 */
		smp_rmb();
		if (!xfs_ail_min(ailp) &&
		    ailp->ail_target == ailp->ail_target_prev) {
			spin_unlock(&ailp->ail_lock);
			freezable_schedule();
			tout = 0;
			continue;
		}
		spin_unlock(&ailp->ail_lock);

		if (tout)
			freezable_schedule_timeout(msecs_to_jiffies(tout));

		__set_current_state(TASK_RUNNING);

		try_to_freeze();

		tout = xfsaild_push(ailp);
	}

	return 0;
}