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
typedef  int u32 ;
struct iss_csi2_device {int /*<<< orphan*/  regs1; int /*<<< orphan*/  iss; } ;
struct iss_csi2_ctrl_cfg {int vp_out_ctrl; scalar_t__ ecc_enable; scalar_t__ vp_only_enable; scalar_t__ vp_clk_enable; scalar_t__ frame_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_CTRL ; 
 int CSI2_CTRL_BURST_SIZE_EXPAND ; 
 int CSI2_CTRL_ECC_EN ; 
 int CSI2_CTRL_ENDIANNESS ; 
 int CSI2_CTRL_FRAME ; 
 int CSI2_CTRL_MFLAG_LEVH_MASK ; 
 int CSI2_CTRL_MFLAG_LEVH_SHIFT ; 
 int CSI2_CTRL_MFLAG_LEVL_MASK ; 
 int CSI2_CTRL_MFLAG_LEVL_SHIFT ; 
 int CSI2_CTRL_NON_POSTED_WRITE ; 
 int CSI2_CTRL_VP_CLK_EN ; 
 int CSI2_CTRL_VP_ONLY_EN ; 
 int CSI2_CTRL_VP_OUT_CTRL_MASK ; 
 int CSI2_CTRL_VP_OUT_CTRL_SHIFT ; 
 int /*<<< orphan*/  iss_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void csi2_recv_config(struct iss_csi2_device *csi2,
			     struct iss_csi2_ctrl_cfg *currctrl)
{
	u32 reg = 0;

	if (currctrl->frame_mode)
		reg |= CSI2_CTRL_FRAME;
	else
		reg &= ~CSI2_CTRL_FRAME;

	if (currctrl->vp_clk_enable)
		reg |= CSI2_CTRL_VP_CLK_EN;
	else
		reg &= ~CSI2_CTRL_VP_CLK_EN;

	if (currctrl->vp_only_enable)
		reg |= CSI2_CTRL_VP_ONLY_EN;
	else
		reg &= ~CSI2_CTRL_VP_ONLY_EN;

	reg &= ~CSI2_CTRL_VP_OUT_CTRL_MASK;
	reg |= currctrl->vp_out_ctrl << CSI2_CTRL_VP_OUT_CTRL_SHIFT;

	if (currctrl->ecc_enable)
		reg |= CSI2_CTRL_ECC_EN;
	else
		reg &= ~CSI2_CTRL_ECC_EN;

	/*
	 * Set MFlag assertion boundaries to:
	 * Low: 4/8 of FIFO size
	 * High: 6/8 of FIFO size
	 */
	reg &= ~(CSI2_CTRL_MFLAG_LEVH_MASK | CSI2_CTRL_MFLAG_LEVL_MASK);
	reg |= (2 << CSI2_CTRL_MFLAG_LEVH_SHIFT) |
	       (4 << CSI2_CTRL_MFLAG_LEVL_SHIFT);

	/* Generation of 16x64-bit bursts (Recommended) */
	reg |= CSI2_CTRL_BURST_SIZE_EXPAND;

	/* Do Non-Posted writes (Recommended) */
	reg |= CSI2_CTRL_NON_POSTED_WRITE;

	/*
	 * Enforce Little endian for all formats, including:
	 * YUV4:2:2 8-bit and YUV4:2:0 Legacy
	 */
	reg |= CSI2_CTRL_ENDIANNESS;

	iss_reg_write(csi2->iss, csi2->regs1, CSI2_CTRL, reg);
}