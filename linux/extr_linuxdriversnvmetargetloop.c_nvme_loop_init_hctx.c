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
struct nvme_loop_queue {int dummy; } ;
struct TYPE_2__ {unsigned int queue_count; } ;
struct nvme_loop_ctrl {TYPE_1__ ctrl; struct nvme_loop_queue* queues; } ;
struct blk_mq_hw_ctx {struct nvme_loop_queue* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static int nvme_loop_init_hctx(struct blk_mq_hw_ctx *hctx, void *data,
		unsigned int hctx_idx)
{
	struct nvme_loop_ctrl *ctrl = data;
	struct nvme_loop_queue *queue = &ctrl->queues[hctx_idx + 1];

	BUG_ON(hctx_idx >= ctrl->ctrl.queue_count);

	hctx->driver_data = queue;
	return 0;
}