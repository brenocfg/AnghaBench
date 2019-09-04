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
struct nvme_rdma_ctrl {int /*<<< orphan*/  reconnect_work; int /*<<< orphan*/  err_work; } ;
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct nvme_rdma_ctrl* to_rdma_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_rdma_stop_ctrl(struct nvme_ctrl *nctrl)
{
	struct nvme_rdma_ctrl *ctrl = to_rdma_ctrl(nctrl);

	cancel_work_sync(&ctrl->err_work);
	cancel_delayed_work_sync(&ctrl->reconnect_work);
}