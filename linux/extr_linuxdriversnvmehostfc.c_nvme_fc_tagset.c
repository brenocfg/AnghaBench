#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvme_fc_queue {size_t qnum; TYPE_3__* ctrl; } ;
struct blk_mq_tags {int dummy; } ;
struct TYPE_5__ {struct blk_mq_tags** tags; } ;
struct TYPE_4__ {struct blk_mq_tags** tags; } ;
struct TYPE_6__ {TYPE_2__ tag_set; TYPE_1__ admin_tag_set; } ;

/* Variables and functions */

__attribute__((used)) static struct blk_mq_tags *
nvme_fc_tagset(struct nvme_fc_queue *queue)
{
	if (queue->qnum == 0)
		return queue->ctrl->admin_tag_set.tags[queue->qnum];

	return queue->ctrl->tag_set.tags[queue->qnum - 1];
}