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
struct fb_var_screeninfo {unsigned int yoffset; scalar_t__ xoffset; } ;
struct TYPE_2__ {scalar_t__ yres; scalar_t__ yres_virtual; unsigned int xres; } ;
struct fb_info {TYPE_1__ var; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TOP_REG ; 

__attribute__((used)) static int g364fb_pan_display(struct fb_var_screeninfo *var, 
			      struct fb_info *info)
{
	if (var->xoffset ||
	    var->yoffset + info->var.yres > info->var.yres_virtual)
		return -EINVAL;

	*(unsigned int *) TOP_REG = var->yoffset * info->var.xres;
	return 0;
}