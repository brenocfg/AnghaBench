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
struct pool_workqueue {int /*<<< orphan*/  unbound_release_work; TYPE_2__* wq; int /*<<< orphan*/  refcnt; TYPE_1__* pool; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int WQ_UNBOUND ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_pwq(struct pool_workqueue *pwq)
{
	lockdep_assert_held(&pwq->pool->lock);
	if (likely(--pwq->refcnt))
		return;
	if (WARN_ON_ONCE(!(pwq->wq->flags & WQ_UNBOUND)))
		return;
	/*
	 * @pwq can't be released under pool->lock, bounce to
	 * pwq_unbound_release_workfn().  This never recurses on the same
	 * pool->lock as this path is taken only for unbound workqueues and
	 * the release work item is scheduled on a per-cpu workqueue.  To
	 * avoid lockdep warning, unbound pool->locks are given lockdep
	 * subclass of 1 in get_unbound_pool().
	 */
	schedule_work(&pwq->unbound_release_work);
}