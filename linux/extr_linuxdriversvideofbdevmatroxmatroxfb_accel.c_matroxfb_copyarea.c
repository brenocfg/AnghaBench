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
struct TYPE_3__ {int /*<<< orphan*/  xres_virtual; } ;
struct TYPE_4__ {TYPE_1__ var; } ;
struct matrox_fb_info {TYPE_2__ fbcon; } ;
struct fb_info {int dummy; } ;
struct fb_copyarea {int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  dx; int /*<<< orphan*/  dy; int /*<<< orphan*/  sx; int /*<<< orphan*/  sy; } ;

/* Variables and functions */
 struct matrox_fb_info* info2minfo (struct fb_info*) ; 
 int /*<<< orphan*/  matrox_accel_bmove (struct matrox_fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void matroxfb_copyarea(struct fb_info* info, const struct fb_copyarea* area) {
	struct matrox_fb_info *minfo = info2minfo(info);

	matrox_accel_bmove(minfo, minfo->fbcon.var.xres_virtual, area->sy, area->sx, area->dy, area->dx, area->height, area->width);
}