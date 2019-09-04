#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mxsfb_info {int sync; TYPE_4__* devdata; scalar_t__ base; int /*<<< orphan*/  dotclk_delay; TYPE_1__* pdev; int /*<<< orphan*/  ld_intf_width; scalar_t__ enabled; } ;
struct TYPE_7__ {int xres; int bits_per_pixel; int yres_virtual; int yres; int vsync_len; int sync; int upper_margin; int lower_margin; int yoffset; scalar_t__ hsync_len; scalar_t__ left_margin; scalar_t__ right_margin; } ;
struct TYPE_6__ {int smem_len; int line_length; int smem_start; } ;
struct fb_info {TYPE_3__ var; TYPE_2__ fix; struct mxsfb_info* par; } ;
struct TYPE_8__ {scalar_t__ next_buf; scalar_t__ transfer_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTRL1_FIFO_CLEAR ; 
 int CTRL1_SET_BYTE_PACKAGING (int) ; 
 int CTRL_BYPASS_COUNT ; 
 int CTRL_MASTER ; 
 int CTRL_SET_BUS_WIDTH (int /*<<< orphan*/ ) ; 
 int CTRL_SET_WORD_LENGTH (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 scalar_t__ LCDC_CTRL ; 
 scalar_t__ LCDC_CTRL1 ; 
 scalar_t__ LCDC_VDCTRL0 ; 
 scalar_t__ LCDC_VDCTRL1 ; 
 scalar_t__ LCDC_VDCTRL2 ; 
 scalar_t__ LCDC_VDCTRL3 ; 
 scalar_t__ LCDC_VDCTRL4 ; 
 int MXSFB_SYNC_DATA_ENABLE_HIGH_ACT ; 
 int MXSFB_SYNC_DOTCLK_FALLING_ACT ; 
 scalar_t__ REG_SET ; 
 int SET_DOTCLK_H_VALID_DATA_CNT (int) ; 
 int SET_HOR_WAIT_CNT (scalar_t__) ; 
 int SET_VERT_WAIT_CNT (int) ; 
#define  STMLCDIF_16BIT 131 
#define  STMLCDIF_18BIT 130 
#define  STMLCDIF_24BIT 129 
#define  STMLCDIF_8BIT 128 
 int TRANSFER_COUNT_SET_HCOUNT (int) ; 
 int TRANSFER_COUNT_SET_VCOUNT (int) ; 
 int VDCTRL0_DOTCLK_ACT_FALLING ; 
 int VDCTRL0_ENABLE_ACT_HIGH ; 
 int VDCTRL0_ENABLE_PRESENT ; 
 int VDCTRL0_HSYNC_ACT_HIGH ; 
 int VDCTRL0_SET_VSYNC_PULSE_WIDTH (int) ; 
 int VDCTRL0_VSYNC_ACT_HIGH ; 
 int VDCTRL0_VSYNC_PERIOD_UNIT ; 
 int VDCTRL0_VSYNC_PULSE_WIDTH_UNIT ; 
 int VDCTRL2_SET_HSYNC_PERIOD (scalar_t__) ; 
 int VDCTRL4_SET_DOTCLK_DLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  mxsfb_disable_axi_clk (struct mxsfb_info*) ; 
 int /*<<< orphan*/  mxsfb_disable_controller (struct fb_info*) ; 
 int /*<<< orphan*/  mxsfb_enable_axi_clk (struct mxsfb_info*) ; 
 int /*<<< orphan*/  mxsfb_enable_controller (struct fb_info*) ; 
 scalar_t__ mxsfb_is_v4 (struct mxsfb_info*) ; 
 int set_hsync_pulse_width (struct mxsfb_info*,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxsfb_set_par(struct fb_info *fb_info)
{
	struct mxsfb_info *host = fb_info->par;
	u32 ctrl, vdctrl0, vdctrl4;
	int line_size, fb_size;
	int reenable = 0;

	line_size =  fb_info->var.xres * (fb_info->var.bits_per_pixel >> 3);
	fb_size = fb_info->var.yres_virtual * line_size;

	if (fb_size > fb_info->fix.smem_len)
		return -ENOMEM;

	fb_info->fix.line_length = line_size;

	/*
	 * It seems, you can't re-program the controller if it is still running.
	 * This may lead into shifted pictures (FIFO issue?).
	 * So, first stop the controller and drain its FIFOs
	 */
	if (host->enabled) {
		reenable = 1;
		mxsfb_disable_controller(fb_info);
	}

	mxsfb_enable_axi_clk(host);

	/* clear the FIFOs */
	writel(CTRL1_FIFO_CLEAR, host->base + LCDC_CTRL1 + REG_SET);

	ctrl = CTRL_BYPASS_COUNT | CTRL_MASTER |
		CTRL_SET_BUS_WIDTH(host->ld_intf_width);

	switch (fb_info->var.bits_per_pixel) {
	case 16:
		dev_dbg(&host->pdev->dev, "Setting up RGB565 mode\n");
		ctrl |= CTRL_SET_WORD_LENGTH(0);
		writel(CTRL1_SET_BYTE_PACKAGING(0xf), host->base + LCDC_CTRL1);
		break;
	case 32:
		dev_dbg(&host->pdev->dev, "Setting up RGB888/666 mode\n");
		ctrl |= CTRL_SET_WORD_LENGTH(3);
		switch (host->ld_intf_width) {
		case STMLCDIF_8BIT:
			mxsfb_disable_axi_clk(host);
			dev_err(&host->pdev->dev,
					"Unsupported LCD bus width mapping\n");
			return -EINVAL;
		case STMLCDIF_16BIT:
		case STMLCDIF_18BIT:
		case STMLCDIF_24BIT:
			/* real 24 bit */
			break;
		}
		/* do not use packed pixels = one pixel per word instead */
		writel(CTRL1_SET_BYTE_PACKAGING(0x7), host->base + LCDC_CTRL1);
		break;
	default:
		mxsfb_disable_axi_clk(host);
		dev_err(&host->pdev->dev, "Unhandled color depth of %u\n",
				fb_info->var.bits_per_pixel);
		return -EINVAL;
	}

	writel(ctrl, host->base + LCDC_CTRL);

	writel(TRANSFER_COUNT_SET_VCOUNT(fb_info->var.yres) |
			TRANSFER_COUNT_SET_HCOUNT(fb_info->var.xres),
			host->base + host->devdata->transfer_count);

	vdctrl0 = VDCTRL0_ENABLE_PRESENT |	/* always in DOTCLOCK mode */
		VDCTRL0_VSYNC_PERIOD_UNIT |
		VDCTRL0_VSYNC_PULSE_WIDTH_UNIT |
		VDCTRL0_SET_VSYNC_PULSE_WIDTH(fb_info->var.vsync_len);
	if (fb_info->var.sync & FB_SYNC_HOR_HIGH_ACT)
		vdctrl0 |= VDCTRL0_HSYNC_ACT_HIGH;
	if (fb_info->var.sync & FB_SYNC_VERT_HIGH_ACT)
		vdctrl0 |= VDCTRL0_VSYNC_ACT_HIGH;
	if (host->sync & MXSFB_SYNC_DATA_ENABLE_HIGH_ACT)
		vdctrl0 |= VDCTRL0_ENABLE_ACT_HIGH;
	if (host->sync & MXSFB_SYNC_DOTCLK_FALLING_ACT)
		vdctrl0 |= VDCTRL0_DOTCLK_ACT_FALLING;

	writel(vdctrl0, host->base + LCDC_VDCTRL0);

	/* frame length in lines */
	writel(fb_info->var.upper_margin + fb_info->var.vsync_len +
		fb_info->var.lower_margin + fb_info->var.yres,
		host->base + LCDC_VDCTRL1);

	/* line length in units of clocks or pixels */
	writel(set_hsync_pulse_width(host, fb_info->var.hsync_len) |
		VDCTRL2_SET_HSYNC_PERIOD(fb_info->var.left_margin +
		fb_info->var.hsync_len + fb_info->var.right_margin +
		fb_info->var.xres),
		host->base + LCDC_VDCTRL2);

	writel(SET_HOR_WAIT_CNT(fb_info->var.left_margin +
		fb_info->var.hsync_len) |
		SET_VERT_WAIT_CNT(fb_info->var.upper_margin +
			fb_info->var.vsync_len),
		host->base + LCDC_VDCTRL3);

	vdctrl4 = SET_DOTCLK_H_VALID_DATA_CNT(fb_info->var.xres);
	if (mxsfb_is_v4(host))
		vdctrl4 |= VDCTRL4_SET_DOTCLK_DLY(host->dotclk_delay);
	writel(vdctrl4, host->base + LCDC_VDCTRL4);

	writel(fb_info->fix.smem_start +
			fb_info->fix.line_length * fb_info->var.yoffset,
			host->base + host->devdata->next_buf);

	mxsfb_disable_axi_clk(host);

	if (reenable)
		mxsfb_enable_controller(fb_info);

	return 0;
}