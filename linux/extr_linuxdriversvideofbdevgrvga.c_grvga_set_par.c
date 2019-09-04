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
struct grvga_par {int clk_sel; TYPE_1__* regs; } ;
struct TYPE_6__ {int yres; int xres; int lower_margin; int right_margin; int vsync_len; int hsync_len; int upper_margin; int left_margin; int bits_per_pixel; int xres_virtual; } ;
struct TYPE_5__ {int line_length; void* visual; } ;
struct fb_info {TYPE_3__ var; TYPE_2__ fix; struct grvga_par* par; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; int /*<<< orphan*/  line_length; int /*<<< orphan*/  sync_length; int /*<<< orphan*/  front_porch; int /*<<< orphan*/  video_length; } ;

/* Variables and functions */
 int EINVAL ; 
 void* FB_VISUAL_PSEUDOCOLOR ; 
 void* FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int grvga_set_par(struct fb_info *info)
{

	u32 func = 0;
	struct grvga_par *par = info->par;

	__raw_writel(((info->var.yres - 1) << 16) | (info->var.xres - 1),
		     &par->regs->video_length);

	__raw_writel((info->var.lower_margin << 16) | (info->var.right_margin),
		     &par->regs->front_porch);

	__raw_writel((info->var.vsync_len << 16) | (info->var.hsync_len),
		     &par->regs->sync_length);

	__raw_writel(((info->var.yres + info->var.lower_margin + info->var.upper_margin + info->var.vsync_len - 1) << 16) |
		     (info->var.xres + info->var.right_margin + info->var.left_margin + info->var.hsync_len - 1),
		     &par->regs->line_length);

	switch (info->var.bits_per_pixel) {
	case 8:
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		func = 1;
		break;
	case 16:
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		func = 2;
		break;
	case 24:
	case 32:
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		func = 3;
		break;
	default:
		return -EINVAL;
	}

	__raw_writel((par->clk_sel << 6) | (func << 4) | 1,
		     &par->regs->status);

	info->fix.line_length = (info->var.xres_virtual*info->var.bits_per_pixel)/8;
	return 0;
}