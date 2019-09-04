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
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct nvme_rdma_ctrl {TYPE_2__ ctrl; TYPE_1__* queues; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_RDMA_Q_LIVE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int nvmf_connect_admin_queue (TYPE_2__*) ; 
 int nvmf_connect_io_queue (TYPE_2__*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_rdma_start_queue(struct nvme_rdma_ctrl *ctrl, int idx)
{
	int ret;

	if (idx)
		ret = nvmf_connect_io_queue(&ctrl->ctrl, idx);
	else
		ret = nvmf_connect_admin_queue(&ctrl->ctrl);

	if (!ret)
		set_bit(NVME_RDMA_Q_LIVE, &ctrl->queues[idx].flags);
	else
		dev_info(ctrl->ctrl.device,
			"failed to connect queue: %d ret=%d\n", idx, ret);
	return ret;
}