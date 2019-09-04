#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mxsfb_info {int enabled; int /*<<< orphan*/  clk; TYPE_2__* devdata; scalar_t__ base; int /*<<< orphan*/  dotclk_delay; int /*<<< orphan*/  ld_intf_width; } ;
struct fb_videomode {int xres; unsigned long yres; int hsync_len; int left_margin; int right_margin; unsigned int vsync_len; unsigned int upper_margin; unsigned int lower_margin; int /*<<< orphan*/  pixclock; int /*<<< orphan*/  sync; int /*<<< orphan*/  vmode; } ;
struct TYPE_6__ {int line_length; unsigned long smem_start; unsigned long smem_len; int ypanstep; } ;
struct TYPE_4__ {int bits_per_pixel; } ;
struct fb_info {TYPE_3__ fix; scalar_t__ screen_base; TYPE_1__ var; struct mxsfb_info* par; } ;
struct TYPE_5__ {scalar_t__ next_buf; scalar_t__ cur_buf; scalar_t__ transfer_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_GET_BUS_WIDTH (int) ; 
 int CTRL_GET_WORD_LENGTH (int) ; 
 int CTRL_RUN ; 
 int EINVAL ; 
 int /*<<< orphan*/  FB_SYNC_HOR_HIGH_ACT ; 
 int /*<<< orphan*/  FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 int GET_HOR_WAIT_CNT (int) ; 
 unsigned int GET_VERT_WAIT_CNT (int) ; 
 int /*<<< orphan*/  KHZ2PICOS (unsigned int) ; 
 scalar_t__ LCDC_CTRL ; 
 scalar_t__ LCDC_VDCTRL0 ; 
 scalar_t__ LCDC_VDCTRL1 ; 
 scalar_t__ LCDC_VDCTRL2 ; 
 scalar_t__ LCDC_VDCTRL3 ; 
 scalar_t__ LCDC_VDCTRL4 ; 
 int /*<<< orphan*/  PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int TRANSFER_COUNT_GET_HCOUNT (int) ; 
 unsigned long TRANSFER_COUNT_GET_VCOUNT (int) ; 
 unsigned int VDCTRL0_GET_VSYNC_PULSE_WIDTH (int) ; 
 int VDCTRL0_HSYNC_ACT_HIGH ; 
 int VDCTRL0_VSYNC_ACT_HIGH ; 
 int VDCTRL2_GET_HSYNC_PERIOD (int) ; 
 int /*<<< orphan*/  VDCTRL4_GET_DOTCLK_DLY (int) ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int get_hsync_pulse_width (struct mxsfb_info*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  mxsfb_disable_axi_clk (struct mxsfb_info*) ; 
 int /*<<< orphan*/  mxsfb_enable_axi_clk (struct mxsfb_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int mxsfb_restore_mode(struct fb_info *fb_info,
			struct fb_videomode *vmode)
{
	struct mxsfb_info *host = fb_info->par;
	unsigned line_count;
	unsigned period;
	unsigned long pa, fbsize;
	int bits_per_pixel, ofs, ret = 0;
	u32 transfer_count, vdctrl0, vdctrl2, vdctrl3, vdctrl4, ctrl;

	mxsfb_enable_axi_clk(host);

	/* Only restore the mode when the controller is running */
	ctrl = readl(host->base + LCDC_CTRL);
	if (!(ctrl & CTRL_RUN)) {
		ret = -EINVAL;
		goto err;
	}

	vdctrl0 = readl(host->base + LCDC_VDCTRL0);
	vdctrl2 = readl(host->base + LCDC_VDCTRL2);
	vdctrl3 = readl(host->base + LCDC_VDCTRL3);
	vdctrl4 = readl(host->base + LCDC_VDCTRL4);

	transfer_count = readl(host->base + host->devdata->transfer_count);

	vmode->xres = TRANSFER_COUNT_GET_HCOUNT(transfer_count);
	vmode->yres = TRANSFER_COUNT_GET_VCOUNT(transfer_count);

	switch (CTRL_GET_WORD_LENGTH(ctrl)) {
	case 0:
		bits_per_pixel = 16;
		break;
	case 3:
		bits_per_pixel = 32;
		break;
	case 1:
	default:
		ret = -EINVAL;
		goto err;
	}

	fb_info->var.bits_per_pixel = bits_per_pixel;

	vmode->pixclock = KHZ2PICOS(clk_get_rate(host->clk) / 1000U);
	vmode->hsync_len = get_hsync_pulse_width(host, vdctrl2);
	vmode->left_margin = GET_HOR_WAIT_CNT(vdctrl3) - vmode->hsync_len;
	vmode->right_margin = VDCTRL2_GET_HSYNC_PERIOD(vdctrl2) -
		vmode->hsync_len - vmode->left_margin - vmode->xres;
	vmode->vsync_len = VDCTRL0_GET_VSYNC_PULSE_WIDTH(vdctrl0);
	period = readl(host->base + LCDC_VDCTRL1);
	vmode->upper_margin = GET_VERT_WAIT_CNT(vdctrl3) - vmode->vsync_len;
	vmode->lower_margin = period - vmode->vsync_len -
		vmode->upper_margin - vmode->yres;

	vmode->vmode = FB_VMODE_NONINTERLACED;

	vmode->sync = 0;
	if (vdctrl0 & VDCTRL0_HSYNC_ACT_HIGH)
		vmode->sync |= FB_SYNC_HOR_HIGH_ACT;
	if (vdctrl0 & VDCTRL0_VSYNC_ACT_HIGH)
		vmode->sync |= FB_SYNC_VERT_HIGH_ACT;

	pr_debug("Reconstructed video mode:\n");
	pr_debug("%dx%d, hsync: %u left: %u, right: %u, vsync: %u, upper: %u, lower: %u\n",
		vmode->xres, vmode->yres, vmode->hsync_len, vmode->left_margin,
		vmode->right_margin, vmode->vsync_len, vmode->upper_margin,
		vmode->lower_margin);
	pr_debug("pixclk: %ldkHz\n", PICOS2KHZ(vmode->pixclock));

	host->ld_intf_width = CTRL_GET_BUS_WIDTH(ctrl);
	host->dotclk_delay = VDCTRL4_GET_DOTCLK_DLY(vdctrl4);

	fb_info->fix.line_length = vmode->xres * (bits_per_pixel >> 3);

	pa = readl(host->base + host->devdata->cur_buf);
	fbsize = fb_info->fix.line_length * vmode->yres;
	if (pa < fb_info->fix.smem_start) {
		ret = -EINVAL;
		goto err;
	}
	if (pa + fbsize > fb_info->fix.smem_start + fb_info->fix.smem_len) {
		ret = -EINVAL;
		goto err;
	}
	ofs = pa - fb_info->fix.smem_start;
	if (ofs) {
		memmove(fb_info->screen_base, fb_info->screen_base + ofs, fbsize);
		writel(fb_info->fix.smem_start, host->base + host->devdata->next_buf);
	}

	line_count = fb_info->fix.smem_len / fb_info->fix.line_length;
	fb_info->fix.ypanstep = 1;

	clk_prepare_enable(host->clk);
	host->enabled = 1;

err:
	if (ret)
		mxsfb_disable_axi_clk(host);

	return ret;
}