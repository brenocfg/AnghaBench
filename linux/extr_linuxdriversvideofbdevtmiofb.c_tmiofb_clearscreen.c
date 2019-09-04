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
struct fb_info {TYPE_2__* fbops; TYPE_1__* mode; } ;
struct fb_fillrect {int /*<<< orphan*/  rop; int /*<<< orphan*/  color; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fb_fillrect ) (struct fb_info*,struct fb_fillrect const*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROP_COPY ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_fillrect const*) ; 

__attribute__((used)) static void tmiofb_clearscreen(struct fb_info *info)
{
	const struct fb_fillrect rect = {
		.dx	= 0,
		.dy	= 0,
		.width	= info->mode->xres,
		.height	= info->mode->yres,
		.color	= 0,
		.rop	= ROP_COPY,
	};

	info->fbops->fb_fillrect(info, &rect);
}