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
struct TYPE_7__ {int length; int offset; scalar_t__ msb_right; } ;
struct TYPE_8__ {int length; int offset; } ;
struct TYPE_6__ {int length; int offset; scalar_t__ msb_right; } ;
struct TYPE_5__ {int length; int offset; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_3__ red; TYPE_4__ transp; TYPE_2__ green; TYPE_1__ blue; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ fbswap ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm2708_fb_set_bitfields(struct fb_var_screeninfo *var)
{
	int ret = 0;

	memset(&var->transp, 0, sizeof(var->transp));

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;

	switch (var->bits_per_pixel) {
	case 1:
	case 2:
	case 4:
	case 8:
		var->red.length = var->bits_per_pixel;
		var->red.offset = 0;
		var->green.length = var->bits_per_pixel;
		var->green.offset = 0;
		var->blue.length = var->bits_per_pixel;
		var->blue.offset = 0;
		break;
	case 16:
		var->red.length = 5;
		var->blue.length = 5;
		/*
		 * Green length can be 5 or 6 depending whether
		 * we're operating in RGB555 or RGB565 mode.
		 */
		if (var->green.length != 5 && var->green.length != 6)
			var->green.length = 6;
		break;
	case 24:
		var->red.length = 8;
		var->blue.length = 8;
		var->green.length = 8;
		break;
	case 32:
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.length = 8;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	/*
	 * >= 16bpp displays have separate colour component bitfields
	 * encoded in the pixel data.  Calculate their position from
	 * the bitfield length defined above.
	 */
	if (ret == 0 && var->bits_per_pixel >= 24 && fbswap) {
		var->blue.offset = 0;
		var->green.offset = var->blue.offset + var->blue.length;
		var->red.offset = var->green.offset + var->green.length;
		var->transp.offset = var->red.offset + var->red.length;
	} else if (ret == 0 && var->bits_per_pixel >= 24) {
		var->red.offset = 0;
		var->green.offset = var->red.offset + var->red.length;
		var->blue.offset = var->green.offset + var->green.length;
		var->transp.offset = var->blue.offset + var->blue.length;
	} else if (ret == 0 && var->bits_per_pixel >= 16) {
		var->blue.offset = 0;
		var->green.offset = var->blue.offset + var->blue.length;
		var->red.offset = var->green.offset + var->green.length;
		var->transp.offset = var->red.offset + var->red.length;
	}

	return ret;
}