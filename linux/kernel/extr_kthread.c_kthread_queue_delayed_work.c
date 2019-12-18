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
struct kthread_work {int dummy; } ;
struct kthread_delayed_work {struct kthread_work work; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kthread_queue_delayed_work (struct kthread_worker*,struct kthread_delayed_work*,unsigned long) ; 
 int /*<<< orphan*/  queuing_blocked (struct kthread_worker*,struct kthread_work*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool kthread_queue_delayed_work(struct kthread_worker *worker,
				struct kthread_delayed_work *dwork,
				unsigned long delay)
{
	struct kthread_work *work = &dwork->work;
	unsigned long flags;
	bool ret = false;

	raw_spin_lock_irqsave(&worker->lock, flags);

	if (!queuing_blocked(worker, work)) {
		__kthread_queue_delayed_work(worker, dwork, delay);
		ret = true;
	}

	raw_spin_unlock_irqrestore(&worker->lock, flags);
	return ret;
}