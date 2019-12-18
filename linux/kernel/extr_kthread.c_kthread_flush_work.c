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
struct TYPE_3__ {int /*<<< orphan*/  next; } ;
struct kthread_worker {int /*<<< orphan*/  lock; TYPE_1__ work_list; struct kthread_work* current_work; } ;
struct TYPE_4__ {int /*<<< orphan*/  next; } ;
struct kthread_work {TYPE_2__ node; struct kthread_worker* worker; } ;
struct kthread_flush_work {int /*<<< orphan*/  done; int /*<<< orphan*/  work; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLETION_INITIALIZER_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTHREAD_WORK_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kthread_flush_work_fn ; 
 int /*<<< orphan*/  kthread_insert_work (struct kthread_worker*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void kthread_flush_work(struct kthread_work *work)
{
	struct kthread_flush_work fwork = {
		KTHREAD_WORK_INIT(fwork.work, kthread_flush_work_fn),
		COMPLETION_INITIALIZER_ONSTACK(fwork.done),
	};
	struct kthread_worker *worker;
	bool noop = false;

	worker = work->worker;
	if (!worker)
		return;

	raw_spin_lock_irq(&worker->lock);
	/* Work must not be used with >1 worker, see kthread_queue_work(). */
	WARN_ON_ONCE(work->worker != worker);

	if (!list_empty(&work->node))
		kthread_insert_work(worker, &fwork.work, work->node.next);
	else if (worker->current_work == work)
		kthread_insert_work(worker, &fwork.work,
				    worker->work_list.next);
	else
		noop = true;

	raw_spin_unlock_irq(&worker->lock);

	if (!noop)
		wait_for_completion(&fwork.done);
}