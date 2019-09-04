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
struct pm2fb_par {int type; } ;

/* Variables and functions */
 int PM2F_DELTA_ORDER_RGB ; 
 int /*<<< orphan*/  PM2F_RD_PALETTE_WIDTH_8 ; 
 int PM2F_SYNCHRONIZATION ; 
 int PM2F_VGA_ENABLE ; 
 int PM2F_VGA_FIXED ; 
 int /*<<< orphan*/  PM2I_RD_BLUE_KEY ; 
 int /*<<< orphan*/  PM2I_RD_COLOR_KEY_CONTROL ; 
 int /*<<< orphan*/  PM2I_RD_CURSOR_CONTROL ; 
 int /*<<< orphan*/  PM2I_RD_GREEN_KEY ; 
 int /*<<< orphan*/  PM2I_RD_MISC_CONTROL ; 
 int /*<<< orphan*/  PM2I_RD_MODE_CONTROL ; 
 int /*<<< orphan*/  PM2I_RD_OVERLAY_KEY ; 
 int /*<<< orphan*/  PM2I_RD_RED_KEY ; 
 int /*<<< orphan*/  PM2R_ALPHA_BLEND_MODE ; 
 int /*<<< orphan*/  PM2R_APERTURE_ONE ; 
 int /*<<< orphan*/  PM2R_APERTURE_TWO ; 
 int /*<<< orphan*/  PM2R_AREA_STIPPLE_MODE ; 
 int /*<<< orphan*/  PM2R_BYPASS_WRITE_MASK ; 
 int /*<<< orphan*/  PM2R_CHIP_CONFIG ; 
 int /*<<< orphan*/  PM2R_COLOR_DDA_MODE ; 
 int /*<<< orphan*/  PM2R_DELTA_MODE ; 
 int /*<<< orphan*/  PM2R_DEPTH_MODE ; 
 int /*<<< orphan*/  PM2R_DITHER_MODE ; 
 int /*<<< orphan*/  PM2R_FB_HARD_WRITE_MASK ; 
 int /*<<< orphan*/  PM2R_FB_PIXEL_OFFSET ; 
 int /*<<< orphan*/  PM2R_FB_READ_PIXEL ; 
 int /*<<< orphan*/  PM2R_FB_SOFT_WRITE_MASK ; 
 int /*<<< orphan*/  PM2R_FB_SOURCE_OFFSET ; 
 int /*<<< orphan*/  PM2R_FB_WINDOW_BASE ; 
 int /*<<< orphan*/  PM2R_FIFO_CONTROL ; 
 int /*<<< orphan*/  PM2R_FILTER_MODE ; 
 int /*<<< orphan*/  PM2R_FOG_MODE ; 
 int /*<<< orphan*/  PM2R_FRAMEBUFFER_WRITE_MASK ; 
 int /*<<< orphan*/  PM2R_LB_READ_FORMAT ; 
 int /*<<< orphan*/  PM2R_LB_READ_MODE ; 
 int /*<<< orphan*/  PM2R_LB_SOURCE_OFFSET ; 
 int /*<<< orphan*/  PM2R_LB_WINDOW_BASE ; 
 int /*<<< orphan*/  PM2R_LB_WRITE_FORMAT ; 
 int /*<<< orphan*/  PM2R_LOGICAL_OP_MODE ; 
 int /*<<< orphan*/  PM2R_RASTERIZER_MODE ; 
 int /*<<< orphan*/  PM2R_RD_PIXEL_MASK ; 
 int /*<<< orphan*/  PM2R_SCISSOR_MODE ; 
 int /*<<< orphan*/  PM2R_STATISTICS_MODE ; 
 int /*<<< orphan*/  PM2R_STENCIL_MODE ; 
 int /*<<< orphan*/  PM2R_TEXEL_LUT_MODE ; 
 int /*<<< orphan*/  PM2R_TEXTURE_ADDRESS_MODE ; 
 int /*<<< orphan*/  PM2R_TEXTURE_COLOR_MODE ; 
 int /*<<< orphan*/  PM2R_TEXTURE_READ_MODE ; 
 int /*<<< orphan*/  PM2R_YUV_MODE ; 
 int /*<<< orphan*/  PM2VI_RD_MISC_CONTROL ; 
#define  PM2_TYPE_PERMEDIA2 129 
#define  PM2_TYPE_PERMEDIA2V 128 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int pm2_RD (struct pm2fb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm2_RDAC_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm2v_RDAC_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reset_config(struct pm2fb_par *p)
{
	WAIT_FIFO(p, 53);
	pm2_WR(p, PM2R_CHIP_CONFIG, pm2_RD(p, PM2R_CHIP_CONFIG) &
			~(PM2F_VGA_ENABLE | PM2F_VGA_FIXED));
	pm2_WR(p, PM2R_BYPASS_WRITE_MASK, ~(0L));
	pm2_WR(p, PM2R_FRAMEBUFFER_WRITE_MASK, ~(0L));
	pm2_WR(p, PM2R_FIFO_CONTROL, 0);
	pm2_WR(p, PM2R_APERTURE_ONE, 0);
	pm2_WR(p, PM2R_APERTURE_TWO, 0);
	pm2_WR(p, PM2R_RASTERIZER_MODE, 0);
	pm2_WR(p, PM2R_DELTA_MODE, PM2F_DELTA_ORDER_RGB);
	pm2_WR(p, PM2R_LB_READ_FORMAT, 0);
	pm2_WR(p, PM2R_LB_WRITE_FORMAT, 0);
	pm2_WR(p, PM2R_LB_READ_MODE, 0);
	pm2_WR(p, PM2R_LB_SOURCE_OFFSET, 0);
	pm2_WR(p, PM2R_FB_SOURCE_OFFSET, 0);
	pm2_WR(p, PM2R_FB_PIXEL_OFFSET, 0);
	pm2_WR(p, PM2R_FB_WINDOW_BASE, 0);
	pm2_WR(p, PM2R_LB_WINDOW_BASE, 0);
	pm2_WR(p, PM2R_FB_SOFT_WRITE_MASK, ~(0L));
	pm2_WR(p, PM2R_FB_HARD_WRITE_MASK, ~(0L));
	pm2_WR(p, PM2R_FB_READ_PIXEL, 0);
	pm2_WR(p, PM2R_DITHER_MODE, 0);
	pm2_WR(p, PM2R_AREA_STIPPLE_MODE, 0);
	pm2_WR(p, PM2R_DEPTH_MODE, 0);
	pm2_WR(p, PM2R_STENCIL_MODE, 0);
	pm2_WR(p, PM2R_TEXTURE_ADDRESS_MODE, 0);
	pm2_WR(p, PM2R_TEXTURE_READ_MODE, 0);
	pm2_WR(p, PM2R_TEXEL_LUT_MODE, 0);
	pm2_WR(p, PM2R_YUV_MODE, 0);
	pm2_WR(p, PM2R_COLOR_DDA_MODE, 0);
	pm2_WR(p, PM2R_TEXTURE_COLOR_MODE, 0);
	pm2_WR(p, PM2R_FOG_MODE, 0);
	pm2_WR(p, PM2R_ALPHA_BLEND_MODE, 0);
	pm2_WR(p, PM2R_LOGICAL_OP_MODE, 0);
	pm2_WR(p, PM2R_STATISTICS_MODE, 0);
	pm2_WR(p, PM2R_SCISSOR_MODE, 0);
	pm2_WR(p, PM2R_FILTER_MODE, PM2F_SYNCHRONIZATION);
	pm2_WR(p, PM2R_RD_PIXEL_MASK, 0xff);
	switch (p->type) {
	case PM2_TYPE_PERMEDIA2:
		pm2_RDAC_WR(p, PM2I_RD_MODE_CONTROL, 0); /* no overlay */
		pm2_RDAC_WR(p, PM2I_RD_CURSOR_CONTROL, 0);
		pm2_RDAC_WR(p, PM2I_RD_MISC_CONTROL, PM2F_RD_PALETTE_WIDTH_8);
		pm2_RDAC_WR(p, PM2I_RD_COLOR_KEY_CONTROL, 0);
		pm2_RDAC_WR(p, PM2I_RD_OVERLAY_KEY, 0);
		pm2_RDAC_WR(p, PM2I_RD_RED_KEY, 0);
		pm2_RDAC_WR(p, PM2I_RD_GREEN_KEY, 0);
		pm2_RDAC_WR(p, PM2I_RD_BLUE_KEY, 0);
		break;
	case PM2_TYPE_PERMEDIA2V:
		pm2v_RDAC_WR(p, PM2VI_RD_MISC_CONTROL, 1); /* 8bit */
		break;
	}
}