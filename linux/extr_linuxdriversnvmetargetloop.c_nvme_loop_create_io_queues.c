#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct nvme_loop_iod {int dummy; } ;
struct TYPE_9__ {int reserved_tags; int cmd_size; int /*<<< orphan*/  timeout; scalar_t__ nr_hw_queues; struct nvme_loop_ctrl* driver_data; int /*<<< orphan*/  flags; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/ * ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  connect_q; TYPE_3__* tagset; scalar_t__ queue_count; TYPE_1__* opts; } ;
struct nvme_loop_ctrl {TYPE_3__ tag_set; TYPE_2__ ctrl; } ;
struct TYPE_7__ {int /*<<< orphan*/  queue_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_F_SHOULD_MERGE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  NVME_IO_TIMEOUT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SG_CHUNK_SIZE ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int blk_mq_alloc_tag_set (TYPE_3__*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (TYPE_3__*) ; 
 int /*<<< orphan*/  blk_mq_init_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int nvme_loop_connect_io_queues (struct nvme_loop_ctrl*) ; 
 int /*<<< orphan*/  nvme_loop_destroy_io_queues (struct nvme_loop_ctrl*) ; 
 int nvme_loop_init_io_queues (struct nvme_loop_ctrl*) ; 
 int /*<<< orphan*/  nvme_loop_mq_ops ; 

__attribute__((used)) static int nvme_loop_create_io_queues(struct nvme_loop_ctrl *ctrl)
{
	int ret;

	ret = nvme_loop_init_io_queues(ctrl);
	if (ret)
		return ret;

	memset(&ctrl->tag_set, 0, sizeof(ctrl->tag_set));
	ctrl->tag_set.ops = &nvme_loop_mq_ops;
	ctrl->tag_set.queue_depth = ctrl->ctrl.opts->queue_size;
	ctrl->tag_set.reserved_tags = 1; /* fabric connect */
	ctrl->tag_set.numa_node = NUMA_NO_NODE;
	ctrl->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	ctrl->tag_set.cmd_size = sizeof(struct nvme_loop_iod) +
		SG_CHUNK_SIZE * sizeof(struct scatterlist);
	ctrl->tag_set.driver_data = ctrl;
	ctrl->tag_set.nr_hw_queues = ctrl->ctrl.queue_count - 1;
	ctrl->tag_set.timeout = NVME_IO_TIMEOUT;
	ctrl->ctrl.tagset = &ctrl->tag_set;

	ret = blk_mq_alloc_tag_set(&ctrl->tag_set);
	if (ret)
		goto out_destroy_queues;

	ctrl->ctrl.connect_q = blk_mq_init_queue(&ctrl->tag_set);
	if (IS_ERR(ctrl->ctrl.connect_q)) {
		ret = PTR_ERR(ctrl->ctrl.connect_q);
		goto out_free_tagset;
	}

	ret = nvme_loop_connect_io_queues(ctrl);
	if (ret)
		goto out_cleanup_connect_q;

	return 0;

out_cleanup_connect_q:
	blk_cleanup_queue(ctrl->ctrl.connect_q);
out_free_tagset:
	blk_mq_free_tag_set(&ctrl->tag_set);
out_destroy_queues:
	nvme_loop_destroy_io_queues(ctrl);
	return ret;
}