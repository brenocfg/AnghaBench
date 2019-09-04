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
struct TYPE_3__ {int sm_addr; } ;
struct sm501fb_par {TYPE_1__ screen; struct sm501fb_info* info; } ;
struct sm501fb_info {scalar_t__ regs2d; } ;
struct TYPE_4__ {int xres_virtual; int yres_virtual; int xres; int bits_per_pixel; } ;
struct fb_info {TYPE_2__ var; struct sm501fb_par* par; } ;
struct fb_copyarea {int width; int height; int sx; int sy; int dx; int dy; } ;

/* Variables and functions */
 scalar_t__ SM501_2D_COLOR_COMPARE_MASK ; 
 scalar_t__ SM501_2D_CONTROL ; 
 scalar_t__ SM501_2D_DESTINATION ; 
 scalar_t__ SM501_2D_DESTINATION_BASE ; 
 scalar_t__ SM501_2D_DIMENSION ; 
 scalar_t__ SM501_2D_MASK ; 
 scalar_t__ SM501_2D_PITCH ; 
 scalar_t__ SM501_2D_SOURCE ; 
 scalar_t__ SM501_2D_SOURCE_BASE ; 
 scalar_t__ SM501_2D_STRETCH ; 
 scalar_t__ SM501_2D_WINDOW_WIDTH ; 
 scalar_t__ sm501fb_sync (struct fb_info*) ; 
 int /*<<< orphan*/  smc501_writel (int,scalar_t__) ; 

__attribute__((used)) static void sm501fb_copyarea(struct fb_info *info, const struct fb_copyarea *area)
{
	struct sm501fb_par  *par = info->par;
	struct sm501fb_info *fbi = par->info;
	int width = area->width;
	int height = area->height;
	int sx = area->sx;
	int sy = area->sy;
	int dx = area->dx;
	int dy = area->dy;
	unsigned long rtl = 0;

	/* source clip */
	if ((sx >= info->var.xres_virtual) ||
	    (sy >= info->var.yres_virtual))
		/* source Area not within virtual screen, skipping */
		return;
	if ((sx + width) >= info->var.xres_virtual)
		width = info->var.xres_virtual - sx - 1;
	if ((sy + height) >= info->var.yres_virtual)
		height = info->var.yres_virtual - sy - 1;

	/* dest clip */
	if ((dx >= info->var.xres_virtual) ||
	    (dy >= info->var.yres_virtual))
		/* Destination Area not within virtual screen, skipping */
		return;
	if ((dx + width) >= info->var.xres_virtual)
		width = info->var.xres_virtual - dx - 1;
	if ((dy + height) >= info->var.yres_virtual)
		height = info->var.yres_virtual - dy - 1;

	if ((sx < dx) || (sy < dy)) {
		rtl = 1 << 27;
		sx += width - 1;
		dx += width - 1;
		sy += height - 1;
		dy += height - 1;
	}

	if (sm501fb_sync(info))
		return;

	/* set the base addresses */
	smc501_writel(par->screen.sm_addr, fbi->regs2d + SM501_2D_SOURCE_BASE);
	smc501_writel(par->screen.sm_addr,
			fbi->regs2d + SM501_2D_DESTINATION_BASE);

	/* set the window width */
	smc501_writel((info->var.xres << 16) | info->var.xres,
	       fbi->regs2d + SM501_2D_WINDOW_WIDTH);

	/* set window stride */
	smc501_writel((info->var.xres_virtual << 16) | info->var.xres_virtual,
	       fbi->regs2d + SM501_2D_PITCH);

	/* set data format */
	switch (info->var.bits_per_pixel) {
	case 8:
		smc501_writel(0, fbi->regs2d + SM501_2D_STRETCH);
		break;
	case 16:
		smc501_writel(0x00100000, fbi->regs2d + SM501_2D_STRETCH);
		break;
	case 32:
		smc501_writel(0x00200000, fbi->regs2d + SM501_2D_STRETCH);
		break;
	}

	/* 2d compare mask */
	smc501_writel(0xffffffff, fbi->regs2d + SM501_2D_COLOR_COMPARE_MASK);

	/* 2d mask */
	smc501_writel(0xffffffff, fbi->regs2d + SM501_2D_MASK);

	/* source and destination x y */
	smc501_writel((sx << 16) | sy, fbi->regs2d + SM501_2D_SOURCE);
	smc501_writel((dx << 16) | dy, fbi->regs2d + SM501_2D_DESTINATION);

	/* w/h */
	smc501_writel((width << 16) | height, fbi->regs2d + SM501_2D_DIMENSION);

	/* do area move */
	smc501_writel(0x800000cc | rtl, fbi->regs2d + SM501_2D_CONTROL);
}