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
struct nvme_rdma_ctrl {int /*<<< orphan*/  err_work; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_CTRL_RESETTING ; 
 int /*<<< orphan*/  nvme_change_ctrl_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_rdma_error_recovery(struct nvme_rdma_ctrl *ctrl)
{
	if (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_RESETTING))
		return;

	queue_work(nvme_wq, &ctrl->err_work);
}