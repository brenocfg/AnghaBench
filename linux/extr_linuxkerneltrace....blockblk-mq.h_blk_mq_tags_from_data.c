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
struct blk_mq_tags {int dummy; } ;
struct blk_mq_alloc_data {int flags; TYPE_1__* hctx; } ;
struct TYPE_2__ {struct blk_mq_tags* tags; struct blk_mq_tags* sched_tags; } ;

/* Variables and functions */
 int BLK_MQ_REQ_INTERNAL ; 

__attribute__((used)) static inline struct blk_mq_tags *blk_mq_tags_from_data(struct blk_mq_alloc_data *data)
{
	if (data->flags & BLK_MQ_REQ_INTERNAL)
		return data->hctx->sched_tags;

	return data->hctx->tags;
}