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
struct TYPE_3__ {scalar_t__ xres; scalar_t__ yres; } ;
struct fb_info {TYPE_2__* fbops; TYPE_1__ var; } ;
struct fb_copyarea {scalar_t__ dx; scalar_t__ sx; scalar_t__ width; scalar_t__ dy; scalar_t__ sy; scalar_t__ height; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fb_copyarea ) (struct fb_info*,struct fb_copyarea*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  lock_fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_copyarea*) ; 
 int /*<<< orphan*/  unlock_fb_info (struct fb_info*) ; 

__attribute__((used)) static int fb_copyarea_user(struct fb_info *info,
			    struct fb_copyarea *copy)
{
	int ret = 0;
	if (!lock_fb_info(info))
		return -ENODEV;
	if (copy->dx >= info->var.xres ||
	    copy->sx >= info->var.xres ||
	    copy->width > info->var.xres ||
	    copy->dy >= info->var.yres ||
	    copy->sy >= info->var.yres ||
	    copy->height > info->var.yres ||
	    copy->dx + copy->width > info->var.xres ||
	    copy->sx + copy->width > info->var.xres ||
	    copy->dy + copy->height > info->var.yres ||
	    copy->sy + copy->height > info->var.yres) {
		ret = -EINVAL;
		goto out;
	}
	info->fbops->fb_copyarea(info, copy);
out:
	unlock_fb_info(info);
	return ret;
}