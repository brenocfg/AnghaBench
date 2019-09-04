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
struct list_head {int dummy; } ;
struct kthread_worker {int /*<<< orphan*/  task; int /*<<< orphan*/  current_work; } ;
struct kthread_work {struct kthread_worker* worker; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_insert_work_sanity_check (struct kthread_worker*,struct kthread_work*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kthread_insert_work(struct kthread_worker *worker,
				struct kthread_work *work,
				struct list_head *pos)
{
	kthread_insert_work_sanity_check(worker, work);

	list_add_tail(&work->node, pos);
	work->worker = worker;
	if (!worker->current_work && likely(worker->task))
		wake_up_process(worker->task);
}