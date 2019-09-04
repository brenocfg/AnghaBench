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
struct TYPE_2__ {int xres_virtual; int yres_virtual; } ;
struct fb_info {int flags; TYPE_1__ var; } ;
struct fb_fillrect {int width; int height; int dx; int dy; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 int /*<<< orphan*/  memcpy (struct fb_fillrect*,struct fb_fillrect const*,int) ; 
 int /*<<< orphan*/  sys_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  unifb_prim_fillrect (struct fb_info*,struct fb_fillrect*) ; 

__attribute__((used)) static void unifb_fillrect(struct fb_info *info,
		const struct fb_fillrect *region)
{
	struct fb_fillrect modded;
	int vxres, vyres;

	if (info->flags & FBINFO_HWACCEL_DISABLED) {
		sys_fillrect(info, region);
		return;
	}

	vxres = info->var.xres_virtual;
	vyres = info->var.yres_virtual;

	memcpy(&modded, region, sizeof(struct fb_fillrect));

	if (!modded.width || !modded.height ||
	    modded.dx >= vxres || modded.dy >= vyres)
		return;

	if (modded.dx + modded.width > vxres)
		modded.width = vxres - modded.dx;
	if (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	unifb_prim_fillrect(info, &modded);
}