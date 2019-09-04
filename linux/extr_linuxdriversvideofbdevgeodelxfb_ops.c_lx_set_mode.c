#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct lxfb_par {int output; } ;
struct TYPE_4__ {unsigned int yres; int xres; int bits_per_pixel; int right_margin; int hsync_len; int left_margin; int lower_margin; int vsync_len; int upper_margin; } ;
struct TYPE_3__ {int line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct lxfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ARB_CFG ; 
 int /*<<< orphan*/  DC_CB_ST_OFFSET ; 
 int /*<<< orphan*/  DC_CURS_ST_OFFSET ; 
 int /*<<< orphan*/  DC_DISPLAY_CFG ; 
 unsigned int DC_DISPLAY_CFG_DCEN ; 
 unsigned int DC_DISPLAY_CFG_DISP_MODE_16BPP ; 
 unsigned int DC_DISPLAY_CFG_DISP_MODE_24BPP ; 
 unsigned int DC_DISPLAY_CFG_DISP_MODE_8BPP ; 
 unsigned int DC_DISPLAY_CFG_GDEN ; 
 unsigned int DC_DISPLAY_CFG_PALB ; 
 unsigned int DC_DISPLAY_CFG_TGEN ; 
 unsigned int DC_DISPLAY_CFG_TRUP ; 
 unsigned int DC_DISPLAY_CFG_VDEN ; 
 unsigned int DC_DISPLAY_CFG_VISL ; 
 int /*<<< orphan*/  DC_DV_CTL ; 
 unsigned int DC_DV_CTL_DV_LINE_SIZE ; 
 unsigned int DC_DV_CTL_DV_LINE_SIZE_1K ; 
 unsigned int DC_DV_CTL_DV_LINE_SIZE_2K ; 
 unsigned int DC_DV_CTL_DV_LINE_SIZE_4K ; 
 unsigned int DC_DV_CTL_DV_LINE_SIZE_8K ; 
 int /*<<< orphan*/  DC_DV_TOP ; 
 unsigned int DC_DV_TOP_DV_TOP_EN ; 
 int /*<<< orphan*/  DC_FB_ACTIVE ; 
 int /*<<< orphan*/  DC_FB_ST_OFFSET ; 
 int /*<<< orphan*/  DC_GENERAL_CFG ; 
 int DC_GENERAL_CFG_DFHPEL_SHIFT ; 
 int DC_GENERAL_CFG_DFHPSL_SHIFT ; 
 unsigned int DC_GENERAL_CFG_DFLE ; 
 unsigned int DC_GENERAL_CFG_FDTY ; 
 int /*<<< orphan*/  DC_GENLK_CTL ; 
 unsigned int DC_GENLK_CTL_ALPHA_FLICK_EN ; 
 unsigned int DC_GENLK_CTL_FLICK_EN ; 
 unsigned int DC_GENLK_CTL_FLICK_SEL_MASK ; 
 int /*<<< orphan*/  DC_GFX_PITCH ; 
 int /*<<< orphan*/  DC_GFX_SCALE ; 
 int /*<<< orphan*/  DC_H_ACTIVE_TIMING ; 
 int /*<<< orphan*/  DC_H_BLANK_TIMING ; 
 int /*<<< orphan*/  DC_H_SYNC_TIMING ; 
 int /*<<< orphan*/  DC_IRQ_FILT_CTL ; 
 int /*<<< orphan*/  DC_LINE_SIZE ; 
 int /*<<< orphan*/  DC_UNLOCK ; 
 unsigned int DC_UNLOCK_LOCK ; 
 unsigned int DC_UNLOCK_UNLOCK ; 
 int /*<<< orphan*/  DC_V_ACTIVE_TIMING ; 
 int /*<<< orphan*/  DC_V_BLANK_TIMING ; 
 int /*<<< orphan*/  DC_V_SYNC_TIMING ; 
 int /*<<< orphan*/  MSR_LX_GLD_MSR_CONFIG ; 
 int MSR_LX_GLD_MSR_CONFIG_FMT ; 
 int MSR_LX_GLD_MSR_CONFIG_FMT_CRT ; 
 int MSR_LX_GLD_MSR_CONFIG_FMT_FP ; 
 int MSR_LX_GLD_MSR_CONFIG_FPC ; 
 int /*<<< orphan*/  MSR_LX_SPARE_MSR ; 
 int MSR_LX_SPARE_MSR_DIS_CFIFO_HGO ; 
 int MSR_LX_SPARE_MSR_DIS_INIT_V_PRI ; 
 int MSR_LX_SPARE_MSR_DIS_VIFO_WM ; 
 int MSR_LX_SPARE_MSR_LOAD_WM_LPEN_M ; 
 int MSR_LX_SPARE_MSR_VFIFO_ARB_SEL ; 
 int MSR_LX_SPARE_MSR_WM_LPEN_OVRD ; 
 int OUTPUT_CRT ; 
 int OUTPUT_PANEL ; 
 int /*<<< orphan*/  lx_graphics_disable (struct fb_info*) ; 
 int /*<<< orphan*/  lx_graphics_enable (struct fb_info*) ; 
 int /*<<< orphan*/  lx_set_clock (struct fb_info*) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 unsigned int read_dc (struct lxfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_dc (struct lxfb_par*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

void lx_set_mode(struct fb_info *info)
{
	struct lxfb_par *par = info->par;
	u64 msrval;

	unsigned int max, dv, val, size;

	unsigned int gcfg, dcfg;
	int hactive, hblankstart, hsyncstart, hsyncend, hblankend, htotal;
	int vactive, vblankstart, vsyncstart, vsyncend, vblankend, vtotal;

	/* Unlock the DC registers */
	write_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);

	lx_graphics_disable(info);

	lx_set_clock(info);

	/* Set output mode */

	rdmsrl(MSR_LX_GLD_MSR_CONFIG, msrval);
	msrval &= ~MSR_LX_GLD_MSR_CONFIG_FMT;

	if (par->output & OUTPUT_PANEL) {
		msrval |= MSR_LX_GLD_MSR_CONFIG_FMT_FP;

		if (par->output & OUTPUT_CRT)
			msrval |= MSR_LX_GLD_MSR_CONFIG_FPC;
		else
			msrval &= ~MSR_LX_GLD_MSR_CONFIG_FPC;
	} else
		msrval |= MSR_LX_GLD_MSR_CONFIG_FMT_CRT;

	wrmsrl(MSR_LX_GLD_MSR_CONFIG, msrval);

	/* Clear the various buffers */
	/* FIXME:  Adjust for panning here */

	write_dc(par, DC_FB_ST_OFFSET, 0);
	write_dc(par, DC_CB_ST_OFFSET, 0);
	write_dc(par, DC_CURS_ST_OFFSET, 0);

	/* FIXME: Add support for interlacing */
	/* FIXME: Add support for scaling */

	val = read_dc(par, DC_GENLK_CTL);
	val &= ~(DC_GENLK_CTL_ALPHA_FLICK_EN | DC_GENLK_CTL_FLICK_EN |
			DC_GENLK_CTL_FLICK_SEL_MASK);

	/* Default scaling params */

	write_dc(par, DC_GFX_SCALE, (0x4000 << 16) | 0x4000);
	write_dc(par, DC_IRQ_FILT_CTL, 0);
	write_dc(par, DC_GENLK_CTL, val);

	/* FIXME:  Support compression */

	if (info->fix.line_length > 4096)
		dv = DC_DV_CTL_DV_LINE_SIZE_8K;
	else if (info->fix.line_length > 2048)
		dv = DC_DV_CTL_DV_LINE_SIZE_4K;
	else if (info->fix.line_length > 1024)
		dv = DC_DV_CTL_DV_LINE_SIZE_2K;
	else
		dv = DC_DV_CTL_DV_LINE_SIZE_1K;

	max = info->fix.line_length * info->var.yres;
	max = (max + 0x3FF) & 0xFFFFFC00;

	write_dc(par, DC_DV_TOP, max | DC_DV_TOP_DV_TOP_EN);

	val = read_dc(par, DC_DV_CTL) & ~DC_DV_CTL_DV_LINE_SIZE;
	write_dc(par, DC_DV_CTL, val | dv);

	size = info->var.xres * (info->var.bits_per_pixel >> 3);

	write_dc(par, DC_GFX_PITCH, info->fix.line_length >> 3);
	write_dc(par, DC_LINE_SIZE, (size + 7) >> 3);

	/* Set default watermark values */

	rdmsrl(MSR_LX_SPARE_MSR, msrval);

	msrval &= ~(MSR_LX_SPARE_MSR_DIS_CFIFO_HGO
			| MSR_LX_SPARE_MSR_VFIFO_ARB_SEL
			| MSR_LX_SPARE_MSR_LOAD_WM_LPEN_M
			| MSR_LX_SPARE_MSR_WM_LPEN_OVRD);
	msrval |= MSR_LX_SPARE_MSR_DIS_VIFO_WM |
			MSR_LX_SPARE_MSR_DIS_INIT_V_PRI;
	wrmsrl(MSR_LX_SPARE_MSR, msrval);

	gcfg = DC_GENERAL_CFG_DFLE;   /* Display fifo enable */
	gcfg |= (0x6 << DC_GENERAL_CFG_DFHPSL_SHIFT) | /* default priority */
			(0xb << DC_GENERAL_CFG_DFHPEL_SHIFT);
	gcfg |= DC_GENERAL_CFG_FDTY;  /* Set the frame dirty mode */

	dcfg  = DC_DISPLAY_CFG_VDEN;  /* Enable video data */
	dcfg |= DC_DISPLAY_CFG_GDEN;  /* Enable graphics */
	dcfg |= DC_DISPLAY_CFG_TGEN;  /* Turn on the timing generator */
	dcfg |= DC_DISPLAY_CFG_TRUP;  /* Update timings immediately */
	dcfg |= DC_DISPLAY_CFG_PALB;  /* Palette bypass in > 8 bpp modes */
	dcfg |= DC_DISPLAY_CFG_VISL;
	dcfg |= DC_DISPLAY_CFG_DCEN;  /* Always center the display */

	/* Set the current BPP mode */

	switch (info->var.bits_per_pixel) {
	case 8:
		dcfg |= DC_DISPLAY_CFG_DISP_MODE_8BPP;
		break;

	case 16:
		dcfg |= DC_DISPLAY_CFG_DISP_MODE_16BPP;
		break;

	case 32:
	case 24:
		dcfg |= DC_DISPLAY_CFG_DISP_MODE_24BPP;
		break;
	}

	/* Now - set up the timings */

	hactive = info->var.xres;
	hblankstart = hactive;
	hsyncstart = hblankstart + info->var.right_margin;
	hsyncend =  hsyncstart + info->var.hsync_len;
	hblankend = hsyncend + info->var.left_margin;
	htotal = hblankend;

	vactive = info->var.yres;
	vblankstart = vactive;
	vsyncstart = vblankstart + info->var.lower_margin;
	vsyncend =  vsyncstart + info->var.vsync_len;
	vblankend = vsyncend + info->var.upper_margin;
	vtotal = vblankend;

	write_dc(par, DC_H_ACTIVE_TIMING, (hactive - 1) | ((htotal - 1) << 16));
	write_dc(par, DC_H_BLANK_TIMING,
			(hblankstart - 1) | ((hblankend - 1) << 16));
	write_dc(par, DC_H_SYNC_TIMING,
			(hsyncstart - 1) | ((hsyncend - 1) << 16));

	write_dc(par, DC_V_ACTIVE_TIMING, (vactive - 1) | ((vtotal - 1) << 16));
	write_dc(par, DC_V_BLANK_TIMING,
			(vblankstart - 1) | ((vblankend - 1) << 16));
	write_dc(par, DC_V_SYNC_TIMING,
			(vsyncstart - 1) | ((vsyncend - 1) << 16));

	write_dc(par, DC_FB_ACTIVE,
			(info->var.xres - 1) << 16 | (info->var.yres - 1));

	/* And re-enable the graphics output */
	lx_graphics_enable(info);

	/* Write the two main configuration registers */
	write_dc(par, DC_DISPLAY_CFG, dcfg);
	write_dc(par, DC_ARB_CFG, 0);
	write_dc(par, DC_GENERAL_CFG, gcfg);

	/* Lock the DC registers */
	write_dc(par, DC_UNLOCK, DC_UNLOCK_LOCK);
}