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
struct jzfb {TYPE_1__* pdata; } ;
struct fb_videomode {int dummy; } ;
struct TYPE_10__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {int offset; int length; } ;
struct TYPE_8__ {int offset; int length; } ;
struct TYPE_7__ {int offset; int length; } ;
struct fb_var_screeninfo {scalar_t__ bits_per_pixel; TYPE_5__ blue; TYPE_4__ green; TYPE_3__ red; TYPE_2__ transp; } ;
struct fb_info {struct jzfb* par; } ;
struct TYPE_6__ {scalar_t__ bpp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fb_videomode_to_var (struct fb_var_screeninfo*,struct fb_videomode*) ; 
 scalar_t__ jzfb_get_controller_bpp (struct jzfb*) ; 
 struct fb_videomode* jzfb_get_mode (struct jzfb*,struct fb_var_screeninfo*) ; 

__attribute__((used)) static int jzfb_check_var(struct fb_var_screeninfo *var, struct fb_info *fb)
{
	struct jzfb *jzfb = fb->par;
	struct fb_videomode *mode;

	if (var->bits_per_pixel != jzfb_get_controller_bpp(jzfb) &&
		var->bits_per_pixel != jzfb->pdata->bpp)
		return -EINVAL;

	mode = jzfb_get_mode(jzfb, var);
	if (mode == NULL)
		return -EINVAL;

	fb_videomode_to_var(var, mode);

	switch (jzfb->pdata->bpp) {
	case 8:
		break;
	case 15:
		var->red.offset = 10;
		var->red.length = 5;
		var->green.offset = 6;
		var->green.length = 5;
		var->blue.offset = 0;
		var->blue.length = 5;
		break;
	case 16:
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		break;
	case 18:
		var->red.offset = 16;
		var->red.length = 6;
		var->green.offset = 8;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 6;
		var->bits_per_pixel = 32;
		break;
	case 32:
	case 24:
		var->transp.offset = 24;
		var->transp.length = 8;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->bits_per_pixel = 32;
		break;
	default:
		break;
	}

	return 0;
}