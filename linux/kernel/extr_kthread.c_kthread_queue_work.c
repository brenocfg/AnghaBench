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
struct kthread_worker {int /*<<< orphan*/  lock; int /*<<< orphan*/  work_list; } ;
struct kthread_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_insert_work (struct kthread_worker*,struct kthread_work*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queuing_blocked (struct kthread_worker*,struct kthread_work*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool kthread_queue_work(struct kthread_worker *worker,
			struct kthread_work *work)
{
	bool ret = false;
	unsigned long flags;

	raw_spin_lock_irqsave(&worker->lock, flags);
	if (!queuing_blocked(worker, work)) {
		kthread_insert_work(worker, work, &worker->work_list);
		ret = true;
	}
	raw_spin_unlock_irqrestore(&worker->lock, flags);
	return ret;
}