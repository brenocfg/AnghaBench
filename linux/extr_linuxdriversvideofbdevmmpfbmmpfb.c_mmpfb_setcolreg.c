#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mmpfb_info {int /*<<< orphan*/ * pseudo_palette; } ;
struct TYPE_4__ {scalar_t__ visual; } ;
struct TYPE_3__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; struct mmpfb_info* par; } ;

/* Variables and functions */
 scalar_t__ FB_VISUAL_PSEUDOCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  chan_to_field (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_rgb (unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int mmpfb_setcolreg(unsigned int regno, unsigned int red,
		unsigned int green, unsigned int blue,
		unsigned int trans, struct fb_info *info)
{
	struct mmpfb_info *fbi = info->par;
	u32 val;

	if (info->fix.visual == FB_VISUAL_TRUECOLOR && regno < 16) {
		val =  chan_to_field(red,   &info->var.red);
		val |= chan_to_field(green, &info->var.green);
		val |= chan_to_field(blue , &info->var.blue);
		fbi->pseudo_palette[regno] = val;
	}

	if (info->fix.visual == FB_VISUAL_PSEUDOCOLOR && regno < 256) {
		val = to_rgb(red, green, blue);
		/* TODO */
	}

	return 0;
}