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
struct workqueue_struct {int flags; struct worker* rescuer; int /*<<< orphan*/  name; } ;
struct worker {int /*<<< orphan*/  task; struct workqueue_struct* rescue_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int WQ_MEM_RECLAIM ; 
 struct worker* alloc_worker (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  kfree (struct worker*) ; 
 int /*<<< orphan*/  kthread_bind_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_create (int /*<<< orphan*/ ,struct worker*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rescuer_thread ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_rescuer(struct workqueue_struct *wq)
{
	struct worker *rescuer;
	int ret;

	if (!(wq->flags & WQ_MEM_RECLAIM))
		return 0;

	rescuer = alloc_worker(NUMA_NO_NODE);
	if (!rescuer)
		return -ENOMEM;

	rescuer->rescue_wq = wq;
	rescuer->task = kthread_create(rescuer_thread, rescuer, "%s", wq->name);
	ret = PTR_ERR_OR_ZERO(rescuer->task);
	if (ret) {
		kfree(rescuer);
		return ret;
	}

	wq->rescuer = rescuer;
	kthread_bind_mask(rescuer->task, cpu_possible_mask);
	wake_up_process(rescuer->task);

	return 0;
}