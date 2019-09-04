#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dasd_ccw_req {int dummy; } ;
struct TYPE_7__ {int cmd_size; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  flags; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  nr_hw_queues; int /*<<< orphan*/ * ops; } ;
struct dasd_block {TYPE_1__* request_queue; TYPE_2__ tag_set; } ;
struct TYPE_6__ {struct dasd_block* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_F_SHOULD_MERGE ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int PTR_ERR (TYPE_1__*) ; 
 int blk_mq_alloc_tag_set (TYPE_2__*) ; 
 TYPE_1__* blk_mq_init_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  dasd_mq_ops ; 
 int /*<<< orphan*/  nr_hw_queues ; 
 int /*<<< orphan*/  queue_depth ; 

__attribute__((used)) static int dasd_alloc_queue(struct dasd_block *block)
{
	int rc;

	block->tag_set.ops = &dasd_mq_ops;
	block->tag_set.cmd_size = sizeof(struct dasd_ccw_req);
	block->tag_set.nr_hw_queues = nr_hw_queues;
	block->tag_set.queue_depth = queue_depth;
	block->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	block->tag_set.numa_node = NUMA_NO_NODE;

	rc = blk_mq_alloc_tag_set(&block->tag_set);
	if (rc)
		return rc;

	block->request_queue = blk_mq_init_queue(&block->tag_set);
	if (IS_ERR(block->request_queue))
		return PTR_ERR(block->request_queue);

	block->request_queue->queuedata = block;

	return 0;
}