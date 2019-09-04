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
struct kthread_work {struct kthread_worker* worker; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kthread_insert_work_sanity_check(struct kthread_worker *worker,
					     struct kthread_work *work)
{
	lockdep_assert_held(&worker->lock);
	WARN_ON_ONCE(!list_empty(&work->node));
	/* Do not use a work with >1 worker, see kthread_queue_work() */
	WARN_ON_ONCE(work->worker && work->worker != worker);
}