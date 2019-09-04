#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ visual; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_1__ fix; struct e3d_info* par; } ;
struct e3d_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  e3d_clut_write (struct e3d_info*,unsigned int,int) ; 

__attribute__((used)) static int e3d_setcolreg(unsigned regno,
			 unsigned red, unsigned green, unsigned blue,
			 unsigned transp, struct fb_info *info)
{
	struct e3d_info *ep = info->par;
	u32 red_8, green_8, blue_8;
	u32 red_10, green_10, blue_10;
	u32 value;

	if (regno >= 256)
		return 1;

	red_8 = red >> 8;
	green_8 = green >> 8;
	blue_8 = blue >> 8;

	value = (blue_8 << 24) | (green_8 << 16) | (red_8 << 8);

	if (info->fix.visual == FB_VISUAL_TRUECOLOR && regno < 16)
		((u32 *)info->pseudo_palette)[regno] = value;


	red_10 = red >> 6;
	green_10 = green >> 6;
	blue_10 = blue >> 6;

	value = (blue_10 << 20) | (green_10 << 10) | (red_10 << 0);
	e3d_clut_write(ep, regno, value);

	return 0;
}