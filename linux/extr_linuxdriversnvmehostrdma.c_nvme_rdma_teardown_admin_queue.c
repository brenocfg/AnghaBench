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
struct TYPE_2__ {int /*<<< orphan*/  admin_q; } ;
struct nvme_rdma_ctrl {TYPE_1__ ctrl; int /*<<< orphan*/  admin_tag_set; int /*<<< orphan*/ * queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_quiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_cancel_request ; 
 int /*<<< orphan*/  nvme_rdma_destroy_admin_queue (struct nvme_rdma_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_rdma_stop_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_rdma_teardown_admin_queue(struct nvme_rdma_ctrl *ctrl,
		bool remove)
{
	blk_mq_quiesce_queue(ctrl->ctrl.admin_q);
	nvme_rdma_stop_queue(&ctrl->queues[0]);
	blk_mq_tagset_busy_iter(&ctrl->admin_tag_set, nvme_cancel_request,
			&ctrl->ctrl);
	blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);
	nvme_rdma_destroy_admin_queue(ctrl, remove);
}