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
struct timer_list {int dummy; } ;
struct kthread_worker {int /*<<< orphan*/  lock; int /*<<< orphan*/  work_list; } ;
struct kthread_work {int /*<<< orphan*/  node; struct kthread_worker* worker; } ;
struct kthread_delayed_work {struct kthread_work work; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct kthread_delayed_work* dwork ; 
 struct kthread_delayed_work* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_insert_work (struct kthread_worker*,struct kthread_work*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

void kthread_delayed_work_timer_fn(struct timer_list *t)
{
	struct kthread_delayed_work *dwork = from_timer(dwork, t, timer);
	struct kthread_work *work = &dwork->work;
	struct kthread_worker *worker = work->worker;
	unsigned long flags;

	/*
	 * This might happen when a pending work is reinitialized.
	 * It means that it is used a wrong way.
	 */
	if (WARN_ON_ONCE(!worker))
		return;

	raw_spin_lock_irqsave(&worker->lock, flags);
	/* Work must not be used with >1 worker, see kthread_queue_work(). */
	WARN_ON_ONCE(work->worker != worker);

	/* Move the work from worker->delayed_work_list. */
	WARN_ON_ONCE(list_empty(&work->node));
	list_del_init(&work->node);
	kthread_insert_work(worker, work, &worker->work_list);

	raw_spin_unlock_irqrestore(&worker->lock, flags);
}