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
struct fb_var_screeninfo {scalar_t__ xoffset; scalar_t__ yoffset; int vmode; } ;
struct TYPE_2__ {scalar_t__ xres_virtual; scalar_t__ xres; scalar_t__ yres_virtual; scalar_t__ yres; scalar_t__ xoffset; scalar_t__ yoffset; int vmode; } ;
struct fb_info {TYPE_1__ var; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VMODE_YWRAP ; 
 int XGIfb_pan_var (struct fb_var_screeninfo*,struct fb_info*) ; 

__attribute__((used)) static int XGIfb_pan_display(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
	int err;

	if (var->xoffset > (info->var.xres_virtual - info->var.xres))
		return -EINVAL;
	if (var->yoffset > (info->var.yres_virtual - info->var.yres))
		return -EINVAL;

	if (var->vmode & FB_VMODE_YWRAP) {
		if (var->yoffset >= info->var.yres_virtual || var->xoffset)
			return -EINVAL;
	} else if (var->xoffset + info->var.xres > info->var.xres_virtual ||
		   var->yoffset + info->var.yres > info->var.yres_virtual) {
		return -EINVAL;
	}
	err = XGIfb_pan_var(var, info);
	if (err < 0)
		return err;

	info->var.xoffset = var->xoffset;
	info->var.yoffset = var->yoffset;
	if (var->vmode & FB_VMODE_YWRAP)
		info->var.vmode |= FB_VMODE_YWRAP;
	else
		info->var.vmode &= ~FB_VMODE_YWRAP;

	return 0;
}