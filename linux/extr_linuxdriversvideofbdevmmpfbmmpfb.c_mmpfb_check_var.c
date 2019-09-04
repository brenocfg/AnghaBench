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
struct mmpfb_info {int fb_size; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xoffset; int xres; int xres_virtual; int yoffset; int yres; int yres_virtual; } ;
struct fb_info {struct mmpfb_info* par; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int mmpfb_check_var(struct fb_var_screeninfo *var,
		struct fb_info *info)
{
	struct mmpfb_info *fbi = info->par;

	if (var->bits_per_pixel == 8)
		return -EINVAL;
	/*
	 * Basic geometry sanity checks.
	 */
	if (var->xoffset + var->xres > var->xres_virtual)
		return -EINVAL;
	if (var->yoffset + var->yres > var->yres_virtual)
		return -EINVAL;

	/*
	 * Check size of framebuffer.
	 */
	if (var->xres_virtual * var->yres_virtual *
			(var->bits_per_pixel >> 3) > fbi->fb_size)
		return -EINVAL;

	return 0;
}