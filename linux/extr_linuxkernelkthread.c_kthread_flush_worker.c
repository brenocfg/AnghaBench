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
struct kthread_worker {int dummy; } ;
struct kthread_flush_work {int /*<<< orphan*/  done; int /*<<< orphan*/  work; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLETION_INITIALIZER_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTHREAD_WORK_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_flush_work_fn ; 
 int /*<<< orphan*/  kthread_queue_work (struct kthread_worker*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void kthread_flush_worker(struct kthread_worker *worker)
{
	struct kthread_flush_work fwork = {
		KTHREAD_WORK_INIT(fwork.work, kthread_flush_work_fn),
		COMPLETION_INITIALIZER_ONSTACK(fwork.done),
	};

	kthread_queue_work(worker, &fwork.work);
	wait_for_completion(&fwork.done);
}