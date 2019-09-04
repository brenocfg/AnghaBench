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
struct TYPE_9__ {int length; unsigned int offset; } ;
struct TYPE_8__ {int length; unsigned int offset; } ;
struct TYPE_7__ {int length; unsigned int offset; } ;
struct TYPE_10__ {TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct TYPE_6__ {unsigned int len; } ;
struct fb_info {TYPE_5__ var; scalar_t__ pseudo_palette; TYPE_1__ cmap; } ;

/* Variables and functions */

__attribute__((used)) static int efifb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info)
{
	/*
	 *  Set a single color register. The values supplied are
	 *  already rounded down to the hardware's capabilities
	 *  (according to the entries in the `var' structure). Return
	 *  != 0 for invalid regno.
	 */

	if (regno >= info->cmap.len)
		return 1;

	if (regno < 16) {
		red   >>= 16 - info->var.red.length;
		green >>= 16 - info->var.green.length;
		blue  >>= 16 - info->var.blue.length;
		((u32 *)(info->pseudo_palette))[regno] =
			(red   << info->var.red.offset)   |
			(green << info->var.green.offset) |
			(blue  << info->var.blue.offset);
	}
	return 0;
}