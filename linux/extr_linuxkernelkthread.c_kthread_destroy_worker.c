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
struct task_struct {int dummy; } ;
struct kthread_worker {int /*<<< orphan*/  work_list; struct task_struct* task; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct kthread_worker*) ; 
 int /*<<< orphan*/  kthread_flush_worker (struct kthread_worker*) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void kthread_destroy_worker(struct kthread_worker *worker)
{
	struct task_struct *task;

	task = worker->task;
	if (WARN_ON(!task))
		return;

	kthread_flush_worker(worker);
	kthread_stop(task);
	WARN_ON(!list_empty(&worker->work_list));
	kfree(worker);
}