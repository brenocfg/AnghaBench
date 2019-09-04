#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_11__ {unsigned int length; unsigned int offset; } ;
struct TYPE_10__ {unsigned int length; unsigned int offset; } ;
struct TYPE_9__ {unsigned int length; unsigned int offset; } ;
struct TYPE_8__ {unsigned int length; } ;
struct TYPE_12__ {int bits_per_pixel; TYPE_5__ blue; TYPE_4__ green; TYPE_3__ red; TYPE_2__ transp; } ;
struct TYPE_7__ {unsigned int len; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_6__ var; TYPE_1__ cmap; } ;

/* Variables and functions */

__attribute__((used)) static int xenfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info)
{
	u32 v;

	if (regno > info->cmap.len)
		return 1;

#define CNVT_TOHW(val, width) ((((val)<<(width))+0x7FFF-(val))>>16)
	red = CNVT_TOHW(red, info->var.red.length);
	green = CNVT_TOHW(green, info->var.green.length);
	blue = CNVT_TOHW(blue, info->var.blue.length);
	transp = CNVT_TOHW(transp, info->var.transp.length);
#undef CNVT_TOHW

	v = (red << info->var.red.offset) |
	    (green << info->var.green.offset) |
	    (blue << info->var.blue.offset);

	switch (info->var.bits_per_pixel) {
	case 16:
	case 24:
	case 32:
		((u32 *)info->pseudo_palette)[regno] = v;
		break;
	}

	return 0;
}