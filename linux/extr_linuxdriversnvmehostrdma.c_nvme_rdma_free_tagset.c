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
struct nvme_rdma_ctrl {int /*<<< orphan*/  device; } ;
struct nvme_ctrl {int dummy; } ;
struct blk_mq_tag_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_tag_set (struct blk_mq_tag_set*) ; 
 int /*<<< orphan*/  nvme_rdma_dev_put (int /*<<< orphan*/ ) ; 
 struct nvme_rdma_ctrl* to_rdma_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_rdma_free_tagset(struct nvme_ctrl *nctrl,
		struct blk_mq_tag_set *set)
{
	struct nvme_rdma_ctrl *ctrl = to_rdma_ctrl(nctrl);

	blk_mq_free_tag_set(set);
	nvme_rdma_dev_put(ctrl->device);
}