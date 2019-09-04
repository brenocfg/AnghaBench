#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fb_var_screeninfo {int rotate; int xres; int yres; int xres_virtual; int yres_virtual; scalar_t__ xoffset; scalar_t__ bits_per_pixel; scalar_t__ grayscale; } ;
struct TYPE_2__ {int rotate; int yres; int xres; scalar_t__ xoffset; scalar_t__ bits_per_pixel; scalar_t__ grayscale; } ;
struct fb_info {TYPE_1__ var; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int goldfish_fb_check_var(struct fb_var_screeninfo *var,
							struct fb_info *info)
{
	if ((var->rotate & 1) != (info->var.rotate & 1)) {
		if ((var->xres != info->var.yres) ||
				(var->yres != info->var.xres) ||
				(var->xres_virtual != info->var.yres) ||
				(var->yres_virtual > info->var.xres * 2) ||
				(var->yres_virtual < info->var.xres)) {
			return -EINVAL;
		}
	} else {
		if ((var->xres != info->var.xres) ||
		   (var->yres != info->var.yres) ||
		   (var->xres_virtual != info->var.xres) ||
		   (var->yres_virtual > info->var.yres * 2) ||
		   (var->yres_virtual < info->var.yres)) {
			return -EINVAL;
		}
	}
	if ((var->xoffset != info->var.xoffset) ||
			(var->bits_per_pixel != info->var.bits_per_pixel) ||
			(var->grayscale != info->var.grayscale)) {
		return -EINVAL;
	}
	return 0;
}