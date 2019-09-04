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
struct TYPE_4__ {scalar_t__ xres_virtual; scalar_t__ yres_virtual; int xres; int bits_per_pixel; } ;
struct fb_info {TYPE_2__ var; struct sm501fb_par* par; } ;
struct fb_fillrect {int width; int height; scalar_t__ dx; scalar_t__ dy; int color; } ;

/* Variables and functions */
 scalar_t__ SM501_2D_COLOR_COMPARE_MASK ; 
 scalar_t__ SM501_2D_CONTROL ; 
 scalar_t__ SM501_2D_DESTINATION ; 
 scalar_t__ SM501_2D_DESTINATION_BASE ; 
 scalar_t__ SM501_2D_DIMENSION ; 
 scalar_t__ SM501_2D_FOREGROUND ; 
 scalar_t__ SM501_2D_MASK ; 
 scalar_t__ SM501_2D_PITCH ; 
 scalar_t__ SM501_2D_SOURCE_BASE ; 
 scalar_t__ SM501_2D_STRETCH ; 
 scalar_t__ SM501_2D_WINDOW_WIDTH ; 
 scalar_t__ sm501fb_sync (struct fb_info*) ; 
 int /*<<< orphan*/  smc501_writel (int,scalar_t__) ; 

__attribute__((used)) static void sm501fb_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct sm501fb_par  *par = info->par;
	struct sm501fb_info *fbi = par->info;
	int width = rect->width, height = rect->height;

	if ((rect->dx >= info->var.xres_virtual) ||
	    (rect->dy >= info->var.yres_virtual))
		/* Rectangle not within virtual screen, skipping */
		return;
	if ((rect->dx + width) >= info->var.xres_virtual)
		width = info->var.xres_virtual - rect->dx - 1;
	if ((rect->dy + height) >= info->var.yres_virtual)
		height = info->var.yres_virtual - rect->dy - 1;

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

	/* colour */
	smc501_writel(rect->color, fbi->regs2d + SM501_2D_FOREGROUND);

	/* x y */
	smc501_writel((rect->dx << 16) | rect->dy,
			fbi->regs2d + SM501_2D_DESTINATION);

	/* w/h */
	smc501_writel((width << 16) | height, fbi->regs2d + SM501_2D_DIMENSION);

	/* do rectangle fill */
	smc501_writel(0x800100cc, fbi->regs2d + SM501_2D_CONTROL);
}