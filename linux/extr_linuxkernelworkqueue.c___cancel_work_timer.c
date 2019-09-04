#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  func; } ;
struct cwt_wait {TYPE_1__ wait; struct work_struct* work; } ;
typedef  int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  TASK_NORMAL ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __flush_work (struct work_struct*,int) ; 
 int /*<<< orphan*/  __wake_up (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct work_struct*) ; 
 int /*<<< orphan*/  clear_work_data (struct work_struct*) ; 
 int /*<<< orphan*/  cwt_wakefn ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  init_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  mark_work_canceling (struct work_struct*) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int try_to_grab_pending (struct work_struct*,int,unsigned long*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 scalar_t__ work_is_canceling (struct work_struct*) ; 
 scalar_t__ wq_online ; 

__attribute__((used)) static bool __cancel_work_timer(struct work_struct *work, bool is_dwork)
{
	static DECLARE_WAIT_QUEUE_HEAD(cancel_waitq);
	unsigned long flags;
	int ret;

	do {
		ret = try_to_grab_pending(work, is_dwork, &flags);
		/*
		 * If someone else is already canceling, wait for it to
		 * finish.  flush_work() doesn't work for PREEMPT_NONE
		 * because we may get scheduled between @work's completion
		 * and the other canceling task resuming and clearing
		 * CANCELING - flush_work() will return false immediately
		 * as @work is no longer busy, try_to_grab_pending() will
		 * return -ENOENT as @work is still being canceled and the
		 * other canceling task won't be able to clear CANCELING as
		 * we're hogging the CPU.
		 *
		 * Let's wait for completion using a waitqueue.  As this
		 * may lead to the thundering herd problem, use a custom
		 * wake function which matches @work along with exclusive
		 * wait and wakeup.
		 */
		if (unlikely(ret == -ENOENT)) {
			struct cwt_wait cwait;

			init_wait(&cwait.wait);
			cwait.wait.func = cwt_wakefn;
			cwait.work = work;

			prepare_to_wait_exclusive(&cancel_waitq, &cwait.wait,
						  TASK_UNINTERRUPTIBLE);
			if (work_is_canceling(work))
				schedule();
			finish_wait(&cancel_waitq, &cwait.wait);
		}
	} while (unlikely(ret < 0));

	/* tell other tasks trying to grab @work to back off */
	mark_work_canceling(work);
	local_irq_restore(flags);

	/*
	 * This allows canceling during early boot.  We know that @work
	 * isn't executing.
	 */
	if (wq_online)
		__flush_work(work, true);

	clear_work_data(work);

	/*
	 * Paired with prepare_to_wait() above so that either
	 * waitqueue_active() is visible here or !work_is_canceling() is
	 * visible there.
	 */
	smp_mb();
	if (waitqueue_active(&cancel_waitq))
		__wake_up(&cancel_waitq, TASK_NORMAL, 1, work);

	return ret;
}