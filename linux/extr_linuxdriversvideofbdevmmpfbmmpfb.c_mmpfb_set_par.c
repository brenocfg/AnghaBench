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
struct mmpfb_info {int /*<<< orphan*/  overlay; scalar_t__ fb_start_dma; int /*<<< orphan*/  path; int /*<<< orphan*/  output_fmt; int /*<<< orphan*/  mode; } ;
struct mmp_mode {int dummy; } ;
struct mmp_addr {scalar_t__* phys; } ;
struct fb_var_screeninfo {int yoffset; int xres_virtual; int xoffset; int bits_per_pixel; } ;
struct fb_info {struct fb_var_screeninfo var; struct mmpfb_info* par; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  fbmode_to_mmpmode (struct mmp_mode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mmp_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmp_overlay_set_addr (int /*<<< orphan*/ ,struct mmp_addr*) ; 
 int /*<<< orphan*/  mmp_path_set_mode (int /*<<< orphan*/ ,struct mmp_mode*) ; 
 int /*<<< orphan*/  mmpfb_set_win (struct fb_info*) ; 
 int var_update (struct fb_info*) ; 

__attribute__((used)) static int mmpfb_set_par(struct fb_info *info)
{
	struct mmpfb_info *fbi = info->par;
	struct fb_var_screeninfo *var = &info->var;
	struct mmp_addr addr;
	struct mmp_mode mode;
	int ret;

	ret = var_update(info);
	if (ret != 0)
		return ret;

	/* set window/path according to new videomode */
	fbmode_to_mmpmode(&mode, &fbi->mode, fbi->output_fmt);
	mmp_path_set_mode(fbi->path, &mode);

	/* set window related info */
	mmpfb_set_win(info);

	/* set address always */
	memset(&addr, 0, sizeof(addr));
	addr.phys[0] = (var->yoffset * var->xres_virtual + var->xoffset)
		* var->bits_per_pixel / 8 + fbi->fb_start_dma;
	mmp_overlay_set_addr(fbi->overlay, &addr);

	return 0;
}