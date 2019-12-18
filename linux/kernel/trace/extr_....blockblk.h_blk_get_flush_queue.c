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
struct request_queue {int dummy; } ;
struct blk_mq_ctx {int dummy; } ;
struct blk_flush_queue {int dummy; } ;
struct TYPE_2__ {struct blk_flush_queue* fq; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_FLUSH ; 
 TYPE_1__* blk_mq_map_queue (struct request_queue*,int /*<<< orphan*/ ,struct blk_mq_ctx*) ; 

__attribute__((used)) static inline struct blk_flush_queue *
blk_get_flush_queue(struct request_queue *q, struct blk_mq_ctx *ctx)
{
	return blk_mq_map_queue(q, REQ_OP_FLUSH, ctx)->fq;
}