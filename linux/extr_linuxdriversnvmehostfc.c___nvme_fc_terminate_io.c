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
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  device; } ;
struct nvme_fc_ctrl {int /*<<< orphan*/  cnum; TYPE_1__ ctrl; } ;

/* Variables and functions */
 scalar_t__ NVME_CTRL_CONNECTING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_change_ctrl_state (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  nvme_fc_delete_association (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_stop_keep_alive (TYPE_1__*) ; 

__attribute__((used)) static void
__nvme_fc_terminate_io(struct nvme_fc_ctrl *ctrl)
{
	nvme_stop_keep_alive(&ctrl->ctrl);

	/* will block will waiting for io to terminate */
	nvme_fc_delete_association(ctrl);

	if (ctrl->ctrl.state != NVME_CTRL_CONNECTING &&
	    !nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_CONNECTING))
		dev_err(ctrl->ctrl.device,
			"NVME-FC{%d}: error_recovery: Couldn't change state "
			"to CONNECTING\n", ctrl->cnum);
}