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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ xres_virtual; scalar_t__ yres_virtual; } ;
struct fb_info {int flags; TYPE_1__ var; } ;
struct fb_copyarea {scalar_t__ sx; scalar_t__ sy; scalar_t__ dx; scalar_t__ dy; scalar_t__ width; scalar_t__ height; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 int /*<<< orphan*/  sys_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  unifb_prim_copyarea (struct fb_info*,struct fb_copyarea*) ; 

__attribute__((used)) static void unifb_copyarea(struct fb_info *info, const struct fb_copyarea *area)
{
	struct fb_copyarea modded;
	u32 vxres, vyres;
	modded.sx = area->sx;
	modded.sy = area->sy;
	modded.dx = area->dx;
	modded.dy = area->dy;
	modded.width = area->width;
	modded.height = area->height;

	if (info->flags & FBINFO_HWACCEL_DISABLED) {
		sys_copyarea(info, area);
		return;
	}

	vxres = info->var.xres_virtual;
	vyres = info->var.yres_virtual;

	if (!modded.width || !modded.height ||
	    modded.sx >= vxres || modded.sy >= vyres ||
	    modded.dx >= vxres || modded.dy >= vyres)
		return;

	if (modded.sx + modded.width > vxres)
		modded.width = vxres - modded.sx;
	if (modded.dx + modded.width > vxres)
		modded.width = vxres - modded.dx;
	if (modded.sy + modded.height > vyres)
		modded.height = vyres - modded.sy;
	if (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	unifb_prim_copyarea(info, &modded);
}