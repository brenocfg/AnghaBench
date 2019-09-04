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
struct pmagbbfb_par {int dummy; } ;
struct TYPE_4__ {int xres; int xres_virtual; int yres; int yres_virtual; int left_margin; int right_margin; int upper_margin; int lower_margin; int hsync_len; int vsync_len; } ;
struct TYPE_3__ {int line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct pmagbbfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFB_REG_VID_HOR ; 
 int /*<<< orphan*/  SFB_REG_VID_VER ; 
 int SFB_VID_HOR_BP_MASK ; 
 int SFB_VID_HOR_BP_SHIFT ; 
 int SFB_VID_HOR_FP_MASK ; 
 int SFB_VID_HOR_FP_SHIFT ; 
 int SFB_VID_HOR_PIX_MASK ; 
 int SFB_VID_HOR_PIX_SHIFT ; 
 int SFB_VID_HOR_SYN_MASK ; 
 int SFB_VID_HOR_SYN_SHIFT ; 
 int SFB_VID_VER_BP_MASK ; 
 int SFB_VID_VER_BP_SHIFT ; 
 int SFB_VID_VER_FP_MASK ; 
 int SFB_VID_VER_FP_SHIFT ; 
 int SFB_VID_VER_SL_MASK ; 
 int SFB_VID_VER_SL_SHIFT ; 
 int SFB_VID_VER_SYN_MASK ; 
 int SFB_VID_VER_SYN_SHIFT ; 
 int sfb_read (struct pmagbbfb_par*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmagbbfb_screen_setup(struct fb_info *info)
{
	struct pmagbbfb_par *par = info->par;

	info->var.xres = ((sfb_read(par, SFB_REG_VID_HOR) >>
			   SFB_VID_HOR_PIX_SHIFT) & SFB_VID_HOR_PIX_MASK) * 4;
	info->var.xres_virtual = info->var.xres;
	info->var.yres = (sfb_read(par, SFB_REG_VID_VER) >>
			  SFB_VID_VER_SL_SHIFT) & SFB_VID_VER_SL_MASK;
	info->var.yres_virtual = info->var.yres;
	info->var.left_margin = ((sfb_read(par, SFB_REG_VID_HOR) >>
				  SFB_VID_HOR_BP_SHIFT) &
				 SFB_VID_HOR_BP_MASK) * 4;
	info->var.right_margin = ((sfb_read(par, SFB_REG_VID_HOR) >>
				   SFB_VID_HOR_FP_SHIFT) &
				  SFB_VID_HOR_FP_MASK) * 4;
	info->var.upper_margin = (sfb_read(par, SFB_REG_VID_VER) >>
				  SFB_VID_VER_BP_SHIFT) & SFB_VID_VER_BP_MASK;
	info->var.lower_margin = (sfb_read(par, SFB_REG_VID_VER) >>
				  SFB_VID_VER_FP_SHIFT) & SFB_VID_VER_FP_MASK;
	info->var.hsync_len = ((sfb_read(par, SFB_REG_VID_HOR) >>
				SFB_VID_HOR_SYN_SHIFT) &
			       SFB_VID_HOR_SYN_MASK) * 4;
	info->var.vsync_len = (sfb_read(par, SFB_REG_VID_VER) >>
			       SFB_VID_VER_SYN_SHIFT) & SFB_VID_VER_SYN_MASK;

	info->fix.line_length = info->var.xres;
}