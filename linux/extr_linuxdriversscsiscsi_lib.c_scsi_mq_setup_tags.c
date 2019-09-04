#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_data_buffer {int dummy; } ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_5__ {int nr_hw_queues; unsigned int cmd_size; int flags; struct Scsi_Host* driver_data; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/ * ops; } ;
struct Scsi_Host {TYPE_2__ tag_set; TYPE_1__* hostt; int /*<<< orphan*/  can_queue; scalar_t__ nr_hw_queues; } ;
struct TYPE_4__ {int cmd_size; int /*<<< orphan*/  tag_alloc_policy; } ;

/* Variables and functions */
 int BLK_ALLOC_POLICY_TO_MQ_FLAG (int /*<<< orphan*/ ) ; 
 int BLK_MQ_F_SG_MERGE ; 
 int BLK_MQ_F_SHOULD_MERGE ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int blk_mq_alloc_tag_set (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scsi_host_get_prot (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_mq_ops ; 
 unsigned int scsi_mq_sgl_size (struct Scsi_Host*) ; 

int scsi_mq_setup_tags(struct Scsi_Host *shost)
{
	unsigned int cmd_size, sgl_size;

	sgl_size = scsi_mq_sgl_size(shost);
	cmd_size = sizeof(struct scsi_cmnd) + shost->hostt->cmd_size + sgl_size;
	if (scsi_host_get_prot(shost))
		cmd_size += sizeof(struct scsi_data_buffer) + sgl_size;

	memset(&shost->tag_set, 0, sizeof(shost->tag_set));
	shost->tag_set.ops = &scsi_mq_ops;
	shost->tag_set.nr_hw_queues = shost->nr_hw_queues ? : 1;
	shost->tag_set.queue_depth = shost->can_queue;
	shost->tag_set.cmd_size = cmd_size;
	shost->tag_set.numa_node = NUMA_NO_NODE;
	shost->tag_set.flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_SG_MERGE;
	shost->tag_set.flags |=
		BLK_ALLOC_POLICY_TO_MQ_FLAG(shost->hostt->tag_alloc_policy);
	shost->tag_set.driver_data = shost;

	return blk_mq_alloc_tag_set(&shost->tag_set);
}