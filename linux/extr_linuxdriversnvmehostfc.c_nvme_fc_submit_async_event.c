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
struct nvme_fc_fcp_op {int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nvme_fc_ctrl {int flags; TYPE_1__ ctrl; struct nvme_fc_fcp_op* aen_ops; int /*<<< orphan*/  lock; } ;
struct nvme_ctrl {int dummy; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 int FCCTRL_TERMIO ; 
 int /*<<< orphan*/  NVMEFC_FCP_NODATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvme_fc_start_fcp_op (struct nvme_fc_ctrl*,int /*<<< orphan*/ ,struct nvme_fc_fcp_op*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct nvme_fc_ctrl* to_fc_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void
nvme_fc_submit_async_event(struct nvme_ctrl *arg)
{
	struct nvme_fc_ctrl *ctrl = to_fc_ctrl(arg);
	struct nvme_fc_fcp_op *aen_op;
	unsigned long flags;
	bool terminating = false;
	blk_status_t ret;

	spin_lock_irqsave(&ctrl->lock, flags);
	if (ctrl->flags & FCCTRL_TERMIO)
		terminating = true;
	spin_unlock_irqrestore(&ctrl->lock, flags);

	if (terminating)
		return;

	aen_op = &ctrl->aen_ops[0];

	ret = nvme_fc_start_fcp_op(ctrl, aen_op->queue, aen_op, 0,
					NVMEFC_FCP_NODATA);
	if (ret)
		dev_err(ctrl->ctrl.device,
			"failed async event work\n");
}