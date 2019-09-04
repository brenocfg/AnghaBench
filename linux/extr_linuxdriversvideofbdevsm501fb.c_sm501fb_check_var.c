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
struct sm501fb_par {struct sm501fb_info* info; } ;
struct sm501fb_info {TYPE_1__* pdata; } ;
struct TYPE_10__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_9__ {int length; int offset; } ;
struct TYPE_8__ {int length; int offset; } ;
struct TYPE_7__ {int length; int offset; } ;
struct fb_var_screeninfo {int hsync_len; int vsync_len; int xres; int right_margin; int yres; int lower_margin; int bits_per_pixel; int xres_virtual; int yres_virtual; TYPE_5__ transp; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct fb_info {struct sm501fb_par* par; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int SM501_FBPD_SWAP_FB_ENDIAN ; 
 int h_total (struct fb_var_screeninfo*) ; 
 int v_total (struct fb_var_screeninfo*) ; 

__attribute__((used)) static int sm501fb_check_var(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
	struct sm501fb_par  *par = info->par;
	struct sm501fb_info *sm  = par->info;
	unsigned long tmp;

	/* check we can fit these values into the registers */

	if (var->hsync_len > 255 || var->vsync_len > 63)
		return -EINVAL;

	/* hdisplay end and hsync start */
	if ((var->xres + var->right_margin) > 4096)
		return -EINVAL;

	/* vdisplay end and vsync start */
	if ((var->yres + var->lower_margin) > 2048)
		return -EINVAL;

	/* hard limits of device */

	if (h_total(var) > 4096 || v_total(var) > 2048)
		return -EINVAL;

	/* check our line length is going to be 128 bit aligned */

	tmp = (var->xres * var->bits_per_pixel) / 8;
	if ((tmp & 15) != 0)
		return -EINVAL;

	/* check the virtual size */

	if (var->xres_virtual > 4096 || var->yres_virtual > 2048)
		return -EINVAL;

	/* can cope with 8,16 or 32bpp */

	if (var->bits_per_pixel <= 8)
		var->bits_per_pixel = 8;
	else if (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
	else if (var->bits_per_pixel == 24)
		var->bits_per_pixel = 32;

	/* set r/g/b positions and validate bpp */
	switch(var->bits_per_pixel) {
	case 8:
		var->red.length		= var->bits_per_pixel;
		var->red.offset		= 0;
		var->green.length	= var->bits_per_pixel;
		var->green.offset	= 0;
		var->blue.length	= var->bits_per_pixel;
		var->blue.offset	= 0;
		var->transp.length	= 0;
		var->transp.offset	= 0;

		break;

	case 16:
		if (sm->pdata->flags & SM501_FBPD_SWAP_FB_ENDIAN) {
			var->blue.offset	= 11;
			var->green.offset	= 5;
			var->red.offset		= 0;
		} else {
			var->red.offset		= 11;
			var->green.offset	= 5;
			var->blue.offset	= 0;
		}
		var->transp.offset	= 0;

		var->red.length		= 5;
		var->green.length	= 6;
		var->blue.length	= 5;
		var->transp.length	= 0;
		break;

	case 32:
		if (sm->pdata->flags & SM501_FBPD_SWAP_FB_ENDIAN) {
			var->transp.offset	= 0;
			var->red.offset		= 8;
			var->green.offset	= 16;
			var->blue.offset	= 24;
		} else {
			var->transp.offset	= 24;
			var->red.offset		= 16;
			var->green.offset	= 8;
			var->blue.offset	= 0;
		}

		var->red.length		= 8;
		var->green.length	= 8;
		var->blue.length	= 8;
		var->transp.length	= 0;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}