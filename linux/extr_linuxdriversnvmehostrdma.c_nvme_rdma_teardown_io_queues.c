#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int queue_count; } ;
struct nvme_rdma_ctrl {TYPE_1__ ctrl; int /*<<< orphan*/  tag_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_cancel_request ; 
 int /*<<< orphan*/  nvme_rdma_destroy_io_queues (struct nvme_rdma_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_rdma_stop_io_queues (struct nvme_rdma_ctrl*) ; 
 int /*<<< orphan*/  nvme_start_queues (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_stop_queues (TYPE_1__*) ; 

__attribute__((used)) static void nvme_rdma_teardown_io_queues(struct nvme_rdma_ctrl *ctrl,
		bool remove)
{
	if (ctrl->ctrl.queue_count > 1) {
		nvme_stop_queues(&ctrl->ctrl);
		nvme_rdma_stop_io_queues(ctrl);
		blk_mq_tagset_busy_iter(&ctrl->tag_set, nvme_cancel_request,
				&ctrl->ctrl);
		if (remove)
			nvme_start_queues(&ctrl->ctrl);
		nvme_rdma_destroy_io_queues(ctrl, remove);
	}
}