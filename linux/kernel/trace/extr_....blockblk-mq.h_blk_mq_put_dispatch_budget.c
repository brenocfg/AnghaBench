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
struct request_queue {TYPE_1__* mq_ops; } ;
struct blk_mq_hw_ctx {struct request_queue* queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put_budget ) (struct blk_mq_hw_ctx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct blk_mq_hw_ctx*) ; 

__attribute__((used)) static inline void blk_mq_put_dispatch_budget(struct blk_mq_hw_ctx *hctx)
{
	struct request_queue *q = hctx->queue;

	if (q->mq_ops->put_budget)
		q->mq_ops->put_budget(hctx);
}