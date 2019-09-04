#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int offset; int length; } ;
struct TYPE_8__ {int offset; int length; } ;
struct TYPE_7__ {int offset; int length; } ;
struct TYPE_6__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; scalar_t__ xres; scalar_t__ xres_virtual; scalar_t__ yres; scalar_t__ yres_virtual; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; TYPE_1__ transp; } ;
struct TYPE_10__ {scalar_t__ dclkmax; scalar_t__ vfmax; scalar_t__ hfmax; } ;
struct fb_info {TYPE_5__ monspecs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ fb_validate_mode (struct fb_var_screeninfo*,struct fb_info*) ; 

__attribute__((used)) static int i740fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	switch (var->bits_per_pixel) {
	case 8:
		var->red.offset	= var->green.offset = var->blue.offset = 0;
		var->red.length	= var->green.length = var->blue.length = 8;
		break;
	case 16:
		switch (var->green.length) {
		default:
		case 5:
			var->red.offset = 10;
			var->green.offset = 5;
			var->blue.offset = 0;
			var->red.length	= 5;
			var->green.length = 5;
			var->blue.length = 5;
			break;
		case 6:
			var->red.offset = 11;
			var->green.offset = 5;
			var->blue.offset = 0;
			var->red.length = var->blue.length = 5;
			break;
		}
		break;
	case 24:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length	= var->green.length = var->blue.length = 8;
		break;
	case 32:
		var->transp.offset = 24;
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->transp.length = 8;
		var->red.length = var->green.length = var->blue.length = 8;
		break;
	default:
		return -EINVAL;
	}

	if (var->xres > var->xres_virtual)
		var->xres_virtual = var->xres;

	if (var->yres > var->yres_virtual)
		var->yres_virtual = var->yres;

	if (info->monspecs.hfmax && info->monspecs.vfmax &&
	    info->monspecs.dclkmax && fb_validate_mode(var, info) < 0)
		return -EINVAL;

	return 0;
}