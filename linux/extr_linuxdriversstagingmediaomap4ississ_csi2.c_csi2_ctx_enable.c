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
typedef  size_t u8 ;
typedef  unsigned int u32 ;
struct iss_csi2_device {int frame_skip; int output; int /*<<< orphan*/  regs1; int /*<<< orphan*/  iss; struct iss_csi2_ctx_cfg* contexts; } ;
struct iss_csi2_ctx_cfg {size_t enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_CTX_CTRL1 (size_t) ; 
 unsigned int CSI2_CTX_CTRL1_COUNT_MASK ; 
 unsigned int CSI2_CTX_CTRL1_COUNT_SHIFT ; 
 unsigned int CSI2_CTX_CTRL1_COUNT_UNLOCK ; 
 unsigned int CSI2_CTX_CTRL1_CTX_EN ; 
 int CSI2_OUTPUT_MEMORY ; 
 unsigned int iss_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void csi2_ctx_enable(struct iss_csi2_device *csi2, u8 ctxnum, u8 enable)
{
	struct iss_csi2_ctx_cfg *ctx = &csi2->contexts[ctxnum];
	u32 reg;

	reg = iss_reg_read(csi2->iss, csi2->regs1, CSI2_CTX_CTRL1(ctxnum));

	if (enable) {
		unsigned int skip = 0;

		if (csi2->frame_skip)
			skip = csi2->frame_skip;
		else if (csi2->output & CSI2_OUTPUT_MEMORY)
			skip = 1;

		reg &= ~CSI2_CTX_CTRL1_COUNT_MASK;
		reg |= CSI2_CTX_CTRL1_COUNT_UNLOCK
		    |  (skip << CSI2_CTX_CTRL1_COUNT_SHIFT)
		    |  CSI2_CTX_CTRL1_CTX_EN;
	} else {
		reg &= ~CSI2_CTX_CTRL1_CTX_EN;
	}

	iss_reg_write(csi2->iss, csi2->regs1, CSI2_CTX_CTRL1(ctxnum), reg);
	ctx->enabled = enable;
}