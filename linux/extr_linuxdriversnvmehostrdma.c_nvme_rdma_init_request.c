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
struct request {int dummy; } ;
struct nvme_rdma_request {struct nvme_rdma_queue* queue; int /*<<< orphan*/  sqe; } ;
struct nvme_rdma_queue {struct nvme_rdma_device* device; } ;
struct nvme_rdma_device {struct ib_device* dev; } ;
struct blk_mq_tag_set {struct nvme_rdma_ctrl* driver_data; } ;
struct nvme_rdma_ctrl {int /*<<< orphan*/  ctrl; struct nvme_rdma_queue* queues; struct blk_mq_tag_set tag_set; } ;
struct nvme_command {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 int nvme_rdma_alloc_qe (struct ib_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* nvme_req (struct request*) ; 

__attribute__((used)) static int nvme_rdma_init_request(struct blk_mq_tag_set *set,
		struct request *rq, unsigned int hctx_idx,
		unsigned int numa_node)
{
	struct nvme_rdma_ctrl *ctrl = set->driver_data;
	struct nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	int queue_idx = (set == &ctrl->tag_set) ? hctx_idx + 1 : 0;
	struct nvme_rdma_queue *queue = &ctrl->queues[queue_idx];
	struct nvme_rdma_device *dev = queue->device;
	struct ib_device *ibdev = dev->dev;
	int ret;

	nvme_req(rq)->ctrl = &ctrl->ctrl;
	ret = nvme_rdma_alloc_qe(ibdev, &req->sqe, sizeof(struct nvme_command),
			DMA_TO_DEVICE);
	if (ret)
		return ret;

	req->queue = queue;

	return 0;
}