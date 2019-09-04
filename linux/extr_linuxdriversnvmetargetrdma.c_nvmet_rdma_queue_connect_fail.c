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
struct rdma_cm_id {int dummy; } ;
struct nvmet_rdma_queue {scalar_t__ state; int /*<<< orphan*/  release_work; int /*<<< orphan*/  idx; int /*<<< orphan*/  queue_list; } ;

/* Variables and functions */
 scalar_t__ NVMET_RDMA_Q_CONNECTING ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_rdma_queue_mutex ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvmet_rdma_queue_connect_fail(struct rdma_cm_id *cm_id,
		struct nvmet_rdma_queue *queue)
{
	WARN_ON_ONCE(queue->state != NVMET_RDMA_Q_CONNECTING);

	mutex_lock(&nvmet_rdma_queue_mutex);
	if (!list_empty(&queue->queue_list))
		list_del_init(&queue->queue_list);
	mutex_unlock(&nvmet_rdma_queue_mutex);

	pr_err("failed to connect queue %d\n", queue->idx);
	schedule_work(&queue->release_work);
}