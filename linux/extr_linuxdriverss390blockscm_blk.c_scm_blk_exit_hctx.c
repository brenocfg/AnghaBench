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
struct scm_queue {int /*<<< orphan*/  scmrq; } ;
struct blk_mq_hw_ctx {struct scm_queue* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scm_queue*) ; 

__attribute__((used)) static void scm_blk_exit_hctx(struct blk_mq_hw_ctx *hctx, unsigned int idx)
{
	struct scm_queue *qd = hctx->driver_data;

	WARN_ON(qd->scmrq);
	kfree(hctx->driver_data);
	hctx->driver_data = NULL;
}