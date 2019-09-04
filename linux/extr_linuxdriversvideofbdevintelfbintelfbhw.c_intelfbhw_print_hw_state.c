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
struct intelfb_info {int dummy; } ;
struct intelfb_hwstate {int dummy; } ;

/* Variables and functions */

void intelfbhw_print_hw_state(struct intelfb_info *dinfo,
			      struct intelfb_hwstate *hw)
{
#if REGDUMP
	int i, m1, m2, n, p1, p2;
	int index = dinfo->pll_index;
	DBG_MSG("intelfbhw_print_hw_state\n");

	if (!hw)
		return;
	/* Read in as much of the HW state as possible. */
	printk("hw state dump start\n");
	printk("	VGA0_DIVISOR:		0x%08x\n", hw->vga0_divisor);
	printk("	VGA1_DIVISOR:		0x%08x\n", hw->vga1_divisor);
	printk("	VGAPD:			0x%08x\n", hw->vga_pd);
	n = (hw->vga0_divisor >> FP_N_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m1 = (hw->vga0_divisor >> FP_M1_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m2 = (hw->vga0_divisor >> FP_M2_DIVISOR_SHIFT) & FP_DIVISOR_MASK;

	intelfbhw_get_p1p2(dinfo, hw->vga_pd, &p1, &p2);

	printk("	VGA0: (m1, m2, n, p1, p2) = (%d, %d, %d, %d, %d)\n",
	       m1, m2, n, p1, p2);
	printk("	VGA0: clock is %d\n",
	       calc_vclock(index, m1, m2, n, p1, p2, 0));

	n = (hw->vga1_divisor >> FP_N_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m1 = (hw->vga1_divisor >> FP_M1_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m2 = (hw->vga1_divisor >> FP_M2_DIVISOR_SHIFT) & FP_DIVISOR_MASK;

	intelfbhw_get_p1p2(dinfo, hw->vga_pd, &p1, &p2);
	printk("	VGA1: (m1, m2, n, p1, p2) = (%d, %d, %d, %d, %d)\n",
	       m1, m2, n, p1, p2);
	printk("	VGA1: clock is %d\n",
	       calc_vclock(index, m1, m2, n, p1, p2, 0));

	printk("	DPLL_A:			0x%08x\n", hw->dpll_a);
	printk("	DPLL_B:			0x%08x\n", hw->dpll_b);
	printk("	FPA0:			0x%08x\n", hw->fpa0);
	printk("	FPA1:			0x%08x\n", hw->fpa1);
	printk("	FPB0:			0x%08x\n", hw->fpb0);
	printk("	FPB1:			0x%08x\n", hw->fpb1);

	n = (hw->fpa0 >> FP_N_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m1 = (hw->fpa0 >> FP_M1_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m2 = (hw->fpa0 >> FP_M2_DIVISOR_SHIFT) & FP_DIVISOR_MASK;

	intelfbhw_get_p1p2(dinfo, hw->dpll_a, &p1, &p2);

	printk("	PLLA0: (m1, m2, n, p1, p2) = (%d, %d, %d, %d, %d)\n",
	       m1, m2, n, p1, p2);
	printk("	PLLA0: clock is %d\n",
	       calc_vclock(index, m1, m2, n, p1, p2, 0));

	n = (hw->fpa1 >> FP_N_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m1 = (hw->fpa1 >> FP_M1_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m2 = (hw->fpa1 >> FP_M2_DIVISOR_SHIFT) & FP_DIVISOR_MASK;

	intelfbhw_get_p1p2(dinfo, hw->dpll_a, &p1, &p2);

	printk("	PLLA1: (m1, m2, n, p1, p2) = (%d, %d, %d, %d, %d)\n",
	       m1, m2, n, p1, p2);
	printk("	PLLA1: clock is %d\n",
	       calc_vclock(index, m1, m2, n, p1, p2, 0));

#if 0
	printk("	PALETTE_A:\n");
	for (i = 0; i < PALETTE_8_ENTRIES)
		printk("	%3d:	0x%08x\n", i, hw->palette_a[i]);
	printk("	PALETTE_B:\n");
	for (i = 0; i < PALETTE_8_ENTRIES)
		printk("	%3d:	0x%08x\n", i, hw->palette_b[i]);
#endif

	printk("	HTOTAL_A:		0x%08x\n", hw->htotal_a);
	printk("	HBLANK_A:		0x%08x\n", hw->hblank_a);
	printk("	HSYNC_A:		0x%08x\n", hw->hsync_a);
	printk("	VTOTAL_A:		0x%08x\n", hw->vtotal_a);
	printk("	VBLANK_A:		0x%08x\n", hw->vblank_a);
	printk("	VSYNC_A:		0x%08x\n", hw->vsync_a);
	printk("	SRC_SIZE_A:		0x%08x\n", hw->src_size_a);
	printk("	BCLRPAT_A:		0x%08x\n", hw->bclrpat_a);
	printk("	HTOTAL_B:		0x%08x\n", hw->htotal_b);
	printk("	HBLANK_B:		0x%08x\n", hw->hblank_b);
	printk("	HSYNC_B:		0x%08x\n", hw->hsync_b);
	printk("	VTOTAL_B:		0x%08x\n", hw->vtotal_b);
	printk("	VBLANK_B:		0x%08x\n", hw->vblank_b);
	printk("	VSYNC_B:		0x%08x\n", hw->vsync_b);
	printk("	SRC_SIZE_B:		0x%08x\n", hw->src_size_b);
	printk("	BCLRPAT_B:		0x%08x\n", hw->bclrpat_b);

	printk("	ADPA:			0x%08x\n", hw->adpa);
	printk("	DVOA:			0x%08x\n", hw->dvoa);
	printk("	DVOB:			0x%08x\n", hw->dvob);
	printk("	DVOC:			0x%08x\n", hw->dvoc);
	printk("	DVOA_SRCDIM:		0x%08x\n", hw->dvoa_srcdim);
	printk("	DVOB_SRCDIM:		0x%08x\n", hw->dvob_srcdim);
	printk("	DVOC_SRCDIM:		0x%08x\n", hw->dvoc_srcdim);
	printk("	LVDS:			0x%08x\n", hw->lvds);

	printk("	PIPEACONF:		0x%08x\n", hw->pipe_a_conf);
	printk("	PIPEBCONF:		0x%08x\n", hw->pipe_b_conf);
	printk("	DISPARB:		0x%08x\n", hw->disp_arb);

	printk("	CURSOR_A_CONTROL:	0x%08x\n", hw->cursor_a_control);
	printk("	CURSOR_B_CONTROL:	0x%08x\n", hw->cursor_b_control);
	printk("	CURSOR_A_BASEADDR:	0x%08x\n", hw->cursor_a_base);
	printk("	CURSOR_B_BASEADDR:	0x%08x\n", hw->cursor_b_base);

	printk("	CURSOR_A_PALETTE:	");
	for (i = 0; i < 4; i++) {
		printk("0x%08x", hw->cursor_a_palette[i]);
		if (i < 3)
			printk(", ");
	}
	printk("\n");
	printk("	CURSOR_B_PALETTE:	");
	for (i = 0; i < 4; i++) {
		printk("0x%08x", hw->cursor_b_palette[i]);
		if (i < 3)
			printk(", ");
	}
	printk("\n");

	printk("	CURSOR_SIZE:		0x%08x\n", hw->cursor_size);

	printk("	DSPACNTR:		0x%08x\n", hw->disp_a_ctrl);
	printk("	DSPBCNTR:		0x%08x\n", hw->disp_b_ctrl);
	printk("	DSPABASE:		0x%08x\n", hw->disp_a_base);
	printk("	DSPBBASE:		0x%08x\n", hw->disp_b_base);
	printk("	DSPASTRIDE:		0x%08x\n", hw->disp_a_stride);
	printk("	DSPBSTRIDE:		0x%08x\n", hw->disp_b_stride);

	printk("	VGACNTRL:		0x%08x\n", hw->vgacntrl);
	printk("	ADD_ID:			0x%08x\n", hw->add_id);

	for (i = 0; i < 7; i++) {
		printk("	SWF0%d			0x%08x\n", i,
			hw->swf0x[i]);
	}
	for (i = 0; i < 7; i++) {
		printk("	SWF1%d			0x%08x\n", i,
			hw->swf1x[i]);
	}
	for (i = 0; i < 3; i++) {
		printk("	SWF3%d			0x%08x\n", i,
		       hw->swf3x[i]);
	}
	for (i = 0; i < 8; i++)
		printk("	FENCE%d			0x%08x\n", i,
		       hw->fence[i]);

	printk("	INSTPM			0x%08x\n", hw->instpm);
	printk("	MEM_MODE		0x%08x\n", hw->mem_mode);
	printk("	FW_BLC_0		0x%08x\n", hw->fw_blc_0);
	printk("	FW_BLC_1		0x%08x\n", hw->fw_blc_1);

	printk("	HWSTAM			0x%04x\n", hw->hwstam);
	printk("	IER			0x%04x\n", hw->ier);
	printk("	IIR			0x%04x\n", hw->iir);
	printk("	IMR			0x%04x\n", hw->imr);
	printk("hw state dump end\n");
#endif
}