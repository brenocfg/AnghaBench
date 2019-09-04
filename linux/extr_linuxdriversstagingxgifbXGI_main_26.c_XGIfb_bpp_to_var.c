#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xgifb_video_info {int video_cmap_len; } ;
struct TYPE_8__ {int offset; int length; } ;
struct TYPE_7__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int offset; int length; } ;
struct TYPE_5__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;

/* Variables and functions */

__attribute__((used)) static void XGIfb_bpp_to_var(struct xgifb_video_info *xgifb_info,
			     struct fb_var_screeninfo *var)
{
	switch (var->bits_per_pixel) {
	case 8:
		var->red.offset = 0;
		var->green.offset = 0;
		var->blue.offset = 0;
		var->red.length = 6;
		var->green.length = 6;
		var->blue.length = 6;
		xgifb_info->video_cmap_len = 256;
		break;
	case 16:
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		xgifb_info->video_cmap_len = 16;
		break;
	case 32:
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 24;
		var->transp.length = 8;
		xgifb_info->video_cmap_len = 16;
		break;
	}
}