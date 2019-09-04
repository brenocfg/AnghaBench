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
struct uvesafb_pal_entry {unsigned int red; unsigned int green; unsigned int blue; scalar_t__ pad; } ;
struct TYPE_9__ {unsigned int offset; } ;
struct TYPE_8__ {unsigned int offset; } ;
struct TYPE_7__ {int offset; } ;
struct TYPE_10__ {int bits_per_pixel; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct TYPE_6__ {unsigned int len; } ;
struct fb_info {TYPE_5__ var; scalar_t__ pseudo_palette; TYPE_1__ cmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int dac_width ; 
 int uvesafb_setpalette (struct uvesafb_pal_entry*,int,unsigned int,struct fb_info*) ; 

__attribute__((used)) static int uvesafb_setcolreg(unsigned regno, unsigned red, unsigned green,
		unsigned blue, unsigned transp,
		struct fb_info *info)
{
	struct uvesafb_pal_entry entry;
	int shift = 16 - dac_width;
	int err = 0;

	if (regno >= info->cmap.len)
		return -EINVAL;

	if (info->var.bits_per_pixel == 8) {
		entry.red   = red   >> shift;
		entry.green = green >> shift;
		entry.blue  = blue  >> shift;
		entry.pad   = 0;

		err = uvesafb_setpalette(&entry, 1, regno, info);
	} else if (regno < 16) {
		switch (info->var.bits_per_pixel) {
		case 16:
			if (info->var.red.offset == 10) {
				/* 1:5:5:5 */
				((u32 *) (info->pseudo_palette))[regno] =
						((red   & 0xf800) >>  1) |
						((green & 0xf800) >>  6) |
						((blue  & 0xf800) >> 11);
			} else {
				/* 0:5:6:5 */
				((u32 *) (info->pseudo_palette))[regno] =
						((red   & 0xf800)      ) |
						((green & 0xfc00) >>  5) |
						((blue  & 0xf800) >> 11);
			}
			break;

		case 24:
		case 32:
			red   >>= 8;
			green >>= 8;
			blue  >>= 8;
			((u32 *)(info->pseudo_palette))[regno] =
				(red   << info->var.red.offset)   |
				(green << info->var.green.offset) |
				(blue  << info->var.blue.offset);
			break;
		}
	}
	return err;
}