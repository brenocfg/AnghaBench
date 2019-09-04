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
struct worker_pool {int dummy; } ;
struct work_struct {int /*<<< orphan*/  entry; } ;
struct pool_workqueue {struct worker_pool* pool; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ __need_more_worker (struct worker_pool*) ; 
 int /*<<< orphan*/  get_pwq (struct pool_workqueue*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  set_work_pwq (struct work_struct*,struct pool_workqueue*,unsigned int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wake_up_worker (struct worker_pool*) ; 

__attribute__((used)) static void insert_work(struct pool_workqueue *pwq, struct work_struct *work,
			struct list_head *head, unsigned int extra_flags)
{
	struct worker_pool *pool = pwq->pool;

	/* we own @work, set data and link */
	set_work_pwq(work, pwq, extra_flags);
	list_add_tail(&work->entry, head);
	get_pwq(pwq);

	/*
	 * Ensure either wq_worker_sleeping() sees the above
	 * list_add_tail() or we see zero nr_running to avoid workers lying
	 * around lazily while there are works to be processed.
	 */
	smp_mb();

	if (__need_more_worker(pool))
		wake_up_worker(pool);
}