#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; int /*<<< orphan*/  device; } ;
struct nvme_fc_ctrl {TYPE_1__ ctrl; int /*<<< orphan*/  cnum; } ;

/* Variables and functions */
#define  NVME_CTRL_CONNECTING 132 
#define  NVME_CTRL_DELETING 131 
#define  NVME_CTRL_LIVE 130 
#define  NVME_CTRL_NEW 129 
#define  NVME_CTRL_RESETTING 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_delete_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_reset_ctrl (TYPE_1__*) ; 

__attribute__((used)) static void
nvme_fc_ctrl_connectivity_loss(struct nvme_fc_ctrl *ctrl)
{
	dev_info(ctrl->ctrl.device,
		"NVME-FC{%d}: controller connectivity lost. Awaiting "
		"Reconnect", ctrl->cnum);

	switch (ctrl->ctrl.state) {
	case NVME_CTRL_NEW:
	case NVME_CTRL_LIVE:
		/*
		 * Schedule a controller reset. The reset will terminate the
		 * association and schedule the reconnect timer.  Reconnects
		 * will be attempted until either the ctlr_loss_tmo
		 * (max_retries * connect_delay) expires or the remoteport's
		 * dev_loss_tmo expires.
		 */
		if (nvme_reset_ctrl(&ctrl->ctrl)) {
			dev_warn(ctrl->ctrl.device,
				"NVME-FC{%d}: Couldn't schedule reset.\n",
				ctrl->cnum);
			nvme_delete_ctrl(&ctrl->ctrl);
		}
		break;

	case NVME_CTRL_CONNECTING:
		/*
		 * The association has already been terminated and the
		 * controller is attempting reconnects.  No need to do anything
		 * futher.  Reconnects will be attempted until either the
		 * ctlr_loss_tmo (max_retries * connect_delay) expires or the
		 * remoteport's dev_loss_tmo expires.
		 */
		break;

	case NVME_CTRL_RESETTING:
		/*
		 * Controller is already in the process of terminating the
		 * association.  No need to do anything further. The reconnect
		 * step will kick in naturally after the association is
		 * terminated.
		 */
		break;

	case NVME_CTRL_DELETING:
	default:
		/* no action to take - let it delete */
		break;
	}
}