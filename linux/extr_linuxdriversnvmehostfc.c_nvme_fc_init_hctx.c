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
struct nvme_fc_ctrl {int dummy; } ;
struct blk_mq_hw_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nvme_fc_init_hctx (struct blk_mq_hw_ctx*,struct nvme_fc_ctrl*,unsigned int) ; 

__attribute__((used)) static int
nvme_fc_init_hctx(struct blk_mq_hw_ctx *hctx, void *data,
		unsigned int hctx_idx)
{
	struct nvme_fc_ctrl *ctrl = data;

	__nvme_fc_init_hctx(hctx, ctrl, hctx_idx + 1);

	return 0;
}