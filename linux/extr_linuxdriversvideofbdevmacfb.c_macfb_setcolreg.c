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
typedef  unsigned int u32 ;
struct TYPE_9__ {unsigned int offset; } ;
struct TYPE_8__ {unsigned int offset; } ;
struct TYPE_7__ {int offset; } ;
struct TYPE_10__ {int bits_per_pixel; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct TYPE_6__ {unsigned int len; } ;
struct fb_info {TYPE_5__ var; scalar_t__ pseudo_palette; TYPE_1__ cmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  macfb_setpalette (unsigned int,unsigned int,unsigned int,unsigned int,struct fb_info*) ; 

__attribute__((used)) static int macfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *fb_info)
{
	/*
	 * Set a single color register. The values supplied are
	 * already rounded down to the hardware's capabilities
	 * (according to the entries in the `var' structure).
	 * Return non-zero for invalid regno.
	 */
	
	if (regno >= fb_info->cmap.len)
		return 1;

	if (fb_info->var.bits_per_pixel <= 8) {
		switch (fb_info->var.bits_per_pixel) {
		case 1:
			/* We shouldn't get here */
			break;
		case 2:
		case 4:
		case 8:
			if (macfb_setpalette)
				macfb_setpalette(regno, red >> 8, green >> 8,
						 blue >> 8, fb_info);
			else
				return 1;
			break;
		}
	} else if (regno < 16) {
		switch (fb_info->var.bits_per_pixel) {
		case 16:
			if (fb_info->var.red.offset == 10) {
				/* 1:5:5:5 */
				((u32*) (fb_info->pseudo_palette))[regno] =
					((red   & 0xf800) >>  1) |
					((green & 0xf800) >>  6) |
					((blue  & 0xf800) >> 11) |
					((transp != 0) << 15);
			} else {
				/* 0:5:6:5 */
				((u32*) (fb_info->pseudo_palette))[regno] =
					((red   & 0xf800) >>  0) |
					((green & 0xfc00) >>  5) |
					((blue  & 0xf800) >> 11);
			}
			break;
		/*
		 * 24-bit colour almost doesn't exist on 68k Macs --
		 * http://support.apple.com/kb/TA28634 (Old Article: 10992)
		 */
		case 24:
		case 32:
			red   >>= 8;
			green >>= 8;
			blue  >>= 8;
			((u32 *)(fb_info->pseudo_palette))[regno] =
				(red   << fb_info->var.red.offset) |
				(green << fb_info->var.green.offset) |
				(blue  << fb_info->var.blue.offset);
			break;
		}
	}

	return 0;
}