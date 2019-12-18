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
struct timer_list {scalar_t__ function; scalar_t__ expires; } ;
struct kthread_worker {int /*<<< orphan*/  delayed_work_list; int /*<<< orphan*/  work_list; } ;
struct kthread_work {struct kthread_worker* worker; int /*<<< orphan*/  node; } ;
struct kthread_delayed_work {struct kthread_work work; struct timer_list timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ kthread_delayed_work_timer_fn ; 
 int /*<<< orphan*/  kthread_insert_work (struct kthread_worker*,struct kthread_work*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_insert_work_sanity_check (struct kthread_worker*,struct kthread_work*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __kthread_queue_delayed_work(struct kthread_worker *worker,
					 struct kthread_delayed_work *dwork,
					 unsigned long delay)
{
	struct timer_list *timer = &dwork->timer;
	struct kthread_work *work = &dwork->work;

	WARN_ON_ONCE(timer->function != kthread_delayed_work_timer_fn);

	/*
	 * If @delay is 0, queue @dwork->work immediately.  This is for
	 * both optimization and correctness.  The earliest @timer can
	 * expire is on the closest next tick and delayed_work users depend
	 * on that there's no such delay when @delay is 0.
	 */
	if (!delay) {
		kthread_insert_work(worker, work, &worker->work_list);
		return;
	}

	/* Be paranoid and try to detect possible races already now. */
	kthread_insert_work_sanity_check(worker, work);

	list_add(&work->node, &worker->delayed_work_list);
	work->worker = worker;
	timer->expires = jiffies + delay;
	add_timer(timer);
}