#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kthread_worker {int /*<<< orphan*/  lock; } ;
struct kthread_work {scalar_t__ canceling; struct kthread_worker* worker; } ;
struct kthread_delayed_work {struct kthread_work work; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __kthread_cancel_work (struct kthread_work*,int,unsigned long*) ; 
 int /*<<< orphan*/  __kthread_queue_delayed_work (struct kthread_worker*,struct kthread_delayed_work*,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool kthread_mod_delayed_work(struct kthread_worker *worker,
			      struct kthread_delayed_work *dwork,
			      unsigned long delay)
{
	struct kthread_work *work = &dwork->work;
	unsigned long flags;
	int ret = false;

	raw_spin_lock_irqsave(&worker->lock, flags);

	/* Do not bother with canceling when never queued. */
	if (!work->worker)
		goto fast_queue;

	/* Work must not be used with >1 worker, see kthread_queue_work() */
	WARN_ON_ONCE(work->worker != worker);

	/* Do not fight with another command that is canceling this work. */
	if (work->canceling)
		goto out;

	ret = __kthread_cancel_work(work, true, &flags);
fast_queue:
	__kthread_queue_delayed_work(worker, dwork, delay);
out:
	raw_spin_unlock_irqrestore(&worker->lock, flags);
	return ret;
}