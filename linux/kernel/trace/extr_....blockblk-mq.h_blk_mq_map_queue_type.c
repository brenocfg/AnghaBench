#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_2__* tag_set; struct blk_mq_hw_ctx** queue_hw_ctx; } ;
struct blk_mq_hw_ctx {int dummy; } ;
typedef  enum hctx_type { ____Placeholder_hctx_type } hctx_type ;
struct TYPE_4__ {TYPE_1__* map; } ;
struct TYPE_3__ {size_t* mq_map; } ;

/* Variables and functions */

__attribute__((used)) static inline struct blk_mq_hw_ctx *blk_mq_map_queue_type(struct request_queue *q,
							  enum hctx_type type,
							  unsigned int cpu)
{
	return q->queue_hw_ctx[q->tag_set->map[type].mq_map[cpu]];
}