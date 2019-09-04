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
typedef  int /*<<< orphan*/  u16 ;
struct nvme_fc_queue {int dummy; } ;
struct TYPE_2__ {int queue_count; } ;
struct nvme_fc_ctrl {struct nvme_fc_queue* queues; TYPE_1__ ctrl; } ;

/* Variables and functions */
 int __nvme_fc_create_hw_queue (struct nvme_fc_ctrl*,struct nvme_fc_queue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nvme_fc_delete_hw_queue (struct nvme_fc_ctrl*,struct nvme_fc_queue*,int) ; 

__attribute__((used)) static int
nvme_fc_create_hw_io_queues(struct nvme_fc_ctrl *ctrl, u16 qsize)
{
	struct nvme_fc_queue *queue = &ctrl->queues[1];
	int i, ret;

	for (i = 1; i < ctrl->ctrl.queue_count; i++, queue++) {
		ret = __nvme_fc_create_hw_queue(ctrl, queue, i, qsize);
		if (ret)
			goto delete_queues;
	}

	return 0;

delete_queues:
	for (; i >= 0; i--)
		__nvme_fc_delete_hw_queue(ctrl, &ctrl->queues[i], i);
	return ret;
}