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
struct kyrofb_info {int XRES; unsigned long YRES; int VFREQ; int HCLK; int PIXCLK; int HFP; int HST; int HBP; int HTot; unsigned long VFP; unsigned long VST; unsigned long VBP; unsigned long VTot; int HSP; int VSP; int /*<<< orphan*/  PIXDEPTH; } ;
struct TYPE_4__ {int /*<<< orphan*/  visual; int /*<<< orphan*/  line_length; } ;
struct TYPE_3__ {int xres; unsigned long yres; int pixclock; int right_margin; int hsync_len; int left_margin; unsigned long lower_margin; unsigned long vsync_len; unsigned long upper_margin; int sync; int /*<<< orphan*/  bits_per_pixel; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; struct kyrofb_info* par; } ;

/* Variables and functions */
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  get_line_length (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kyro_dev_video_mode_set (struct fb_info*) ; 

__attribute__((used)) static int kyrofb_set_par(struct fb_info *info)
{
	struct kyrofb_info *par = info->par;
	unsigned long lineclock;
	unsigned long frameclock;

	/* Actual resolution */
	par->XRES = info->var.xres;
	par->YRES = info->var.yres;

	/* pixel depth */
	par->PIXDEPTH = info->var.bits_per_pixel;

	/* Refresh rate */
	/* time for a line in ns */
	lineclock = (info->var.pixclock * (info->var.xres +
				    info->var.right_margin +
				    info->var.hsync_len +
				    info->var.left_margin)) / 1000;


	/* time for a frame in ns (precision in 32bpp) */
	frameclock = lineclock * (info->var.yres +
				  info->var.lower_margin +
				  info->var.vsync_len +
				  info->var.upper_margin);

	/* Calculate refresh rate and horrizontal clocks */
	par->VFREQ = (1000000000 + (frameclock / 2)) / frameclock;
	par->HCLK = (1000000000 + (lineclock / 2)) / lineclock;
	par->PIXCLK = ((1000000000 + (info->var.pixclock / 2))
					/ info->var.pixclock) * 10;

	/* calculate horizontal timings */
	par->HFP = info->var.right_margin;
	par->HST = info->var.hsync_len;
	par->HBP = info->var.left_margin;
	par->HTot = par->XRES + par->HBP + par->HST + par->HFP;

	/* calculate vertical timings */
	par->VFP = info->var.lower_margin;
	par->VST = info->var.vsync_len;
	par->VBP = info->var.upper_margin;
	par->VTot = par->YRES + par->VBP + par->VST + par->VFP;

	par->HSP = (info->var.sync & FB_SYNC_HOR_HIGH_ACT) ? 1 : 0;
	par->VSP = (info->var.sync & FB_SYNC_VERT_HIGH_ACT) ? 1 : 0;

	kyro_dev_video_mode_set(info);

	/* length of a line in bytes    */
	info->fix.line_length = get_line_length(par->XRES, par->PIXDEPTH);
	info->fix.visual = FB_VISUAL_TRUECOLOR;

	return 0;
}