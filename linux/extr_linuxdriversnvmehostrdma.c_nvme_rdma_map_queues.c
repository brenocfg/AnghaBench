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
struct nvme_rdma_ctrl {TYPE_1__* device; } ;
struct blk_mq_tag_set {struct nvme_rdma_ctrl* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int blk_mq_rdma_map_queues (struct blk_mq_tag_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_rdma_map_queues(struct blk_mq_tag_set *set)
{
	struct nvme_rdma_ctrl *ctrl = set->driver_data;

	return blk_mq_rdma_map_queues(set, ctrl->device->dev, 0);
}