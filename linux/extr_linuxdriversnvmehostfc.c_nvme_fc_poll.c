#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct nvme_fc_queue {int /*<<< orphan*/  lldd_handle; struct nvme_fc_ctrl* ctrl; } ;
struct nvme_fc_fcp_op {int /*<<< orphan*/  state; } ;
struct nvme_fc_ctrl {TYPE_2__* lport; } ;
struct blk_mq_hw_ctx {struct nvme_fc_queue* driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  localport; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* poll_queue ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ FCPOP_STATE_ACTIVE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct nvme_fc_fcp_op* blk_mq_rq_to_pdu (struct request*) ; 
 struct request* blk_mq_tag_to_rq (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nvme_fc_tagset (struct nvme_fc_queue*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvme_fc_poll(struct blk_mq_hw_ctx *hctx, unsigned int tag)

{
	struct nvme_fc_queue *queue = hctx->driver_data;
	struct nvme_fc_ctrl *ctrl = queue->ctrl;
	struct request *req;
	struct nvme_fc_fcp_op *op;

	req = blk_mq_tag_to_rq(nvme_fc_tagset(queue), tag);
	if (!req)
		return 0;

	op = blk_mq_rq_to_pdu(req);

	if ((atomic_read(&op->state) == FCPOP_STATE_ACTIVE) &&
		 (ctrl->lport->ops->poll_queue))
		ctrl->lport->ops->poll_queue(&ctrl->lport->localport,
						 queue->lldd_handle);

	return ((atomic_read(&op->state) != FCPOP_STATE_ACTIVE));
}