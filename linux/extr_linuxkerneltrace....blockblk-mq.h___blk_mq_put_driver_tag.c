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
struct request {int tag; int rq_flags; int /*<<< orphan*/  mq_ctx; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  nr_active; int /*<<< orphan*/  tags; } ;

/* Variables and functions */
 int RQF_MQ_INFLIGHT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_put_tag (struct blk_mq_hw_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void __blk_mq_put_driver_tag(struct blk_mq_hw_ctx *hctx,
					   struct request *rq)
{
	blk_mq_put_tag(hctx, hctx->tags, rq->mq_ctx, rq->tag);
	rq->tag = -1;

	if (rq->rq_flags & RQF_MQ_INFLIGHT) {
		rq->rq_flags &= ~RQF_MQ_INFLIGHT;
		atomic_dec(&hctx->nr_active);
	}
}