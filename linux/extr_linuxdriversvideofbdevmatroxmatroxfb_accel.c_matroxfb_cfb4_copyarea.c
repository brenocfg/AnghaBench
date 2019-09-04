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
struct TYPE_3__ {int xres_virtual; } ;
struct TYPE_4__ {TYPE_1__ var; } ;
struct matrox_fb_info {TYPE_2__ fbcon; } ;
struct fb_info {int dummy; } ;
struct fb_copyarea {int sx; int dx; int width; int /*<<< orphan*/  height; int /*<<< orphan*/  dy; int /*<<< orphan*/  sy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 struct matrox_fb_info* info2minfo (struct fb_info*) ; 
 int /*<<< orphan*/  matrox_accel_bmove_lin (struct matrox_fb_info*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void matroxfb_cfb4_copyarea(struct fb_info* info, const struct fb_copyarea* area) {
	struct matrox_fb_info *minfo = info2minfo(info);

	if ((area->sx | area->dx | area->width) & 1)
		cfb_copyarea(info, area);
	else
		matrox_accel_bmove_lin(minfo, minfo->fbcon.var.xres_virtual >> 1, area->sy, area->sx >> 1, area->dy, area->dx >> 1, area->height, area->width >> 1);
}