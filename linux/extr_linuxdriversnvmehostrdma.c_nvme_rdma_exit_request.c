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
struct request {int dummy; } ;
struct nvme_rdma_request {int /*<<< orphan*/  sqe; } ;
struct nvme_rdma_queue {struct nvme_rdma_device* device; } ;
struct nvme_rdma_device {int /*<<< orphan*/  dev; } ;
struct blk_mq_tag_set {struct nvme_rdma_ctrl* driver_data; } ;
struct nvme_rdma_ctrl {struct nvme_rdma_queue* queues; struct blk_mq_tag_set tag_set; } ;
struct nvme_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  nvme_rdma_free_qe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_rdma_exit_request(struct blk_mq_tag_set *set,
		struct request *rq, unsigned int hctx_idx)
{
	struct nvme_rdma_ctrl *ctrl = set->driver_data;
	struct nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	int queue_idx = (set == &ctrl->tag_set) ? hctx_idx + 1 : 0;
	struct nvme_rdma_queue *queue = &ctrl->queues[queue_idx];
	struct nvme_rdma_device *dev = queue->device;

	nvme_rdma_free_qe(dev->dev, &req->sqe, sizeof(struct nvme_command),
			DMA_TO_DEVICE);
}