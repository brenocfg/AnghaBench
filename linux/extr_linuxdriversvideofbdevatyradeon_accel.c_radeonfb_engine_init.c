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
struct radeonfb_info {int fb_local_base; int pitch; unsigned long dp_gui_master_cntl; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_PITCH_OFFSET ; 
 int DEFAULT_SC_BOTTOM_MAX ; 
 int /*<<< orphan*/  DEFAULT_SC_BOTTOM_RIGHT ; 
 int DEFAULT_SC_RIGHT_MAX ; 
 int /*<<< orphan*/  DEFAULT_SC_TOP_LEFT ; 
 int /*<<< orphan*/  DP_BRUSH_BKGD_CLR ; 
 int /*<<< orphan*/  DP_BRUSH_FRGD_CLR ; 
 int /*<<< orphan*/  DP_DATATYPE ; 
 int /*<<< orphan*/  DP_GUI_MASTER_CNTL ; 
 int /*<<< orphan*/  DP_SRC_BKGD_CLR ; 
 int /*<<< orphan*/  DP_SRC_FRGD_CLR ; 
 int /*<<< orphan*/  DP_WRITE_MSK ; 
 int /*<<< orphan*/  DST_LINE_END ; 
 int /*<<< orphan*/  DST_LINE_START ; 
 int /*<<< orphan*/  DST_PITCH_OFFSET ; 
 int GMC_BRUSH_SOLID_COLOR ; 
 unsigned long GMC_CLR_CMP_CNTL_DIS ; 
 int GMC_SRC_DATATYPE_COLOR ; 
 int /*<<< orphan*/  HOST_BIG_ENDIAN_EN ; 
 int INREG (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_R300_VARIANT (struct radeonfb_info*) ; 
 int /*<<< orphan*/  MC_FB_LOCATION ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTREGP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RB2D_DC_AUTOFLUSH_ENABLE ; 
 int RB2D_DC_DC_DISABLE_IGNORE_PE ; 
 int /*<<< orphan*/  RB2D_DSTCACHE_MODE ; 
 int /*<<< orphan*/  RB3D_CNTL ; 
 int /*<<< orphan*/  SRC_PITCH_OFFSET ; 
 int /*<<< orphan*/  radeon_engine_idle () ; 
 int /*<<< orphan*/  radeon_fifo_wait (int) ; 
 unsigned long radeon_get_dstbpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeonfb_engine_reset (struct radeonfb_info*) ; 

void radeonfb_engine_init (struct radeonfb_info *rinfo)
{
	unsigned long temp;

	/* disable 3D engine */
	OUTREG(RB3D_CNTL, 0);

	radeonfb_engine_reset(rinfo);

	radeon_fifo_wait (1);
	if (IS_R300_VARIANT(rinfo)) {
		OUTREG(RB2D_DSTCACHE_MODE, INREG(RB2D_DSTCACHE_MODE) |
		       RB2D_DC_AUTOFLUSH_ENABLE |
		       RB2D_DC_DC_DISABLE_IGNORE_PE);
	} else {
		/* This needs to be double checked with ATI. Latest X driver
		 * completely "forgets" to set this register on < r3xx, and
		 * we used to just write 0 there... I'll keep the 0 and update
		 * that when we have sorted things out on X side.
		 */
		OUTREG(RB2D_DSTCACHE_MODE, 0);
	}

	radeon_fifo_wait (3);
	/* We re-read MC_FB_LOCATION from card as it can have been
	 * modified by XFree drivers (ouch !)
	 */
	rinfo->fb_local_base = INREG(MC_FB_LOCATION) << 16;

	OUTREG(DEFAULT_PITCH_OFFSET, (rinfo->pitch << 0x16) |
				     (rinfo->fb_local_base >> 10));
	OUTREG(DST_PITCH_OFFSET, (rinfo->pitch << 0x16) | (rinfo->fb_local_base >> 10));
	OUTREG(SRC_PITCH_OFFSET, (rinfo->pitch << 0x16) | (rinfo->fb_local_base >> 10));

	radeon_fifo_wait (1);
#if defined(__BIG_ENDIAN)
	OUTREGP(DP_DATATYPE, HOST_BIG_ENDIAN_EN, ~HOST_BIG_ENDIAN_EN);
#else
	OUTREGP(DP_DATATYPE, 0, ~HOST_BIG_ENDIAN_EN);
#endif
	radeon_fifo_wait (2);
	OUTREG(DEFAULT_SC_TOP_LEFT, 0);
	OUTREG(DEFAULT_SC_BOTTOM_RIGHT, (DEFAULT_SC_RIGHT_MAX |
					 DEFAULT_SC_BOTTOM_MAX));

	temp = radeon_get_dstbpp(rinfo->depth);
	rinfo->dp_gui_master_cntl = ((temp << 8) | GMC_CLR_CMP_CNTL_DIS);

	radeon_fifo_wait (1);
	OUTREG(DP_GUI_MASTER_CNTL, (rinfo->dp_gui_master_cntl |
				    GMC_BRUSH_SOLID_COLOR |
				    GMC_SRC_DATATYPE_COLOR));

	radeon_fifo_wait (7);

	/* clear line drawing regs */
	OUTREG(DST_LINE_START, 0);
	OUTREG(DST_LINE_END, 0);

	/* set brush color regs */
	OUTREG(DP_BRUSH_FRGD_CLR, 0xffffffff);
	OUTREG(DP_BRUSH_BKGD_CLR, 0x00000000);

	/* set source color regs */
	OUTREG(DP_SRC_FRGD_CLR, 0xffffffff);
	OUTREG(DP_SRC_BKGD_CLR, 0x00000000);

	/* default write mask */
	OUTREG(DP_WRITE_MSK, 0xffffffff);

	radeon_engine_idle ();
}