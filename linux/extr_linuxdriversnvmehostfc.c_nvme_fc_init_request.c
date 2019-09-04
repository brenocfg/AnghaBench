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
struct nvme_fc_queue {int /*<<< orphan*/  rqcnt; } ;
struct nvme_fc_fcp_op {int dummy; } ;
struct blk_mq_tag_set {struct nvme_fc_ctrl* driver_data; } ;
struct nvme_fc_ctrl {int /*<<< orphan*/  ctrl; struct nvme_fc_queue* queues; struct blk_mq_tag_set tag_set; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ctrl; } ;

/* Variables and functions */
 int __nvme_fc_init_request (struct nvme_fc_ctrl*,struct nvme_fc_queue*,struct nvme_fc_fcp_op*,struct request*,int /*<<< orphan*/ ) ; 
 struct nvme_fc_fcp_op* blk_mq_rq_to_pdu (struct request*) ; 
 TYPE_1__* nvme_req (struct request*) ; 

__attribute__((used)) static int
nvme_fc_init_request(struct blk_mq_tag_set *set, struct request *rq,
		unsigned int hctx_idx, unsigned int numa_node)
{
	struct nvme_fc_ctrl *ctrl = set->driver_data;
	struct nvme_fc_fcp_op *op = blk_mq_rq_to_pdu(rq);
	int queue_idx = (set == &ctrl->tag_set) ? hctx_idx + 1 : 0;
	struct nvme_fc_queue *queue = &ctrl->queues[queue_idx];

	nvme_req(rq)->ctrl = &ctrl->ctrl;
	return __nvme_fc_init_request(ctrl, queue, op, rq, queue->rqcnt++);
}