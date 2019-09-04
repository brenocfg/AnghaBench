#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvmet_rdma_queue {int /*<<< orphan*/  idx; int /*<<< orphan*/  host_qid; int /*<<< orphan*/  recv_queue_size; int /*<<< orphan*/  cmds; TYPE_1__* dev; int /*<<< orphan*/  nvme_sq; } ;
struct TYPE_2__ {int /*<<< orphan*/  srq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvmet_rdma_queue*) ; 
 int /*<<< orphan*/  nvmet_rdma_destroy_queue_ib (struct nvmet_rdma_queue*) ; 
 int /*<<< orphan*/  nvmet_rdma_free_cmds (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvmet_rdma_free_rsps (struct nvmet_rdma_queue*) ; 
 int /*<<< orphan*/  nvmet_rdma_queue_ida ; 
 int /*<<< orphan*/  nvmet_sq_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvmet_rdma_free_queue(struct nvmet_rdma_queue *queue)
{
	pr_debug("freeing queue %d\n", queue->idx);

	nvmet_sq_destroy(&queue->nvme_sq);

	nvmet_rdma_destroy_queue_ib(queue);
	if (!queue->dev->srq) {
		nvmet_rdma_free_cmds(queue->dev, queue->cmds,
				queue->recv_queue_size,
				!queue->host_qid);
	}
	nvmet_rdma_free_rsps(queue);
	ida_simple_remove(&nvmet_rdma_queue_ida, queue->idx);
	kfree(queue);
}