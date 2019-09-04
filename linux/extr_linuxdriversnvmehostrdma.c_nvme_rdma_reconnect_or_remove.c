#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; TYPE_1__* opts; int /*<<< orphan*/  device; } ;
struct nvme_rdma_ctrl {TYPE_2__ ctrl; int /*<<< orphan*/  reconnect_work; } ;
struct TYPE_4__ {int reconnect_delay; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ NVME_CTRL_CONNECTING ; 
 scalar_t__ NVME_CTRL_LIVE ; 
 scalar_t__ NVME_CTRL_NEW ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nvme_delete_ctrl (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_wq ; 
 scalar_t__ nvmf_should_reconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void nvme_rdma_reconnect_or_remove(struct nvme_rdma_ctrl *ctrl)
{
	/* If we are resetting/deleting then do nothing */
	if (ctrl->ctrl.state != NVME_CTRL_CONNECTING) {
		WARN_ON_ONCE(ctrl->ctrl.state == NVME_CTRL_NEW ||
			ctrl->ctrl.state == NVME_CTRL_LIVE);
		return;
	}

	if (nvmf_should_reconnect(&ctrl->ctrl)) {
		dev_info(ctrl->ctrl.device, "Reconnecting in %d seconds...\n",
			ctrl->ctrl.opts->reconnect_delay);
		queue_delayed_work(nvme_wq, &ctrl->reconnect_work,
				ctrl->ctrl.opts->reconnect_delay * HZ);
	} else {
		nvme_delete_ctrl(&ctrl->ctrl);
	}
}