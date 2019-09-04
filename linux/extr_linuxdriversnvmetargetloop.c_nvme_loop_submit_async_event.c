#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvme_loop_queue {int /*<<< orphan*/  nvme_sq; int /*<<< orphan*/  nvme_cq; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  command_id; int /*<<< orphan*/  opcode; } ;
struct TYPE_6__ {TYPE_1__ common; } ;
struct nvme_loop_iod {int /*<<< orphan*/  work; int /*<<< orphan*/  req; TYPE_3__ cmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct nvme_loop_ctrl {TYPE_2__ ctrl; struct nvme_loop_iod async_event_iod; struct nvme_loop_queue* queues; } ;
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_AQ_BLK_MQ_DEPTH ; 
 int /*<<< orphan*/  NVME_CMD_SGL_METABUF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_admin_async_event ; 
 int /*<<< orphan*/  nvme_loop_ops ; 
 int /*<<< orphan*/  nvmet_req_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct nvme_loop_ctrl* to_loop_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_loop_submit_async_event(struct nvme_ctrl *arg)
{
	struct nvme_loop_ctrl *ctrl = to_loop_ctrl(arg);
	struct nvme_loop_queue *queue = &ctrl->queues[0];
	struct nvme_loop_iod *iod = &ctrl->async_event_iod;

	memset(&iod->cmd, 0, sizeof(iod->cmd));
	iod->cmd.common.opcode = nvme_admin_async_event;
	iod->cmd.common.command_id = NVME_AQ_BLK_MQ_DEPTH;
	iod->cmd.common.flags |= NVME_CMD_SGL_METABUF;

	if (!nvmet_req_init(&iod->req, &queue->nvme_cq, &queue->nvme_sq,
			&nvme_loop_ops)) {
		dev_err(ctrl->ctrl.device, "failed async event work\n");
		return;
	}

	schedule_work(&iod->work);
}