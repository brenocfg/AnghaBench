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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ visual; } ;
struct TYPE_3__ {scalar_t__ xres_virtual; scalar_t__ yres_virtual; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_2__ fix; TYPE_1__ var; } ;
struct fb_fillrect {scalar_t__ width; scalar_t__ height; scalar_t__ dx; scalar_t__ dy; size_t color; int rop; } ;

/* Variables and functions */
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int GDC_CMD_BLT_FILL ; 
 int GDC_CMD_BODY_FORE_COLOR ; 
 int GDC_REG_MODE_BITMAP ; 
 int GDC_ROP_COPY ; 
 int GDC_ROP_XOR ; 
 int GDC_TYPE_DRAWRECTP ; 
 int GDC_TYPE_SETCOLORREGISTER ; 
 int GDC_TYPE_SETREGISTER ; 
#define  ROP_COPY 129 
#define  ROP_XOR 128 
 int /*<<< orphan*/  mb862xxfb_write_fifo (int,scalar_t__*,struct fb_info*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mb86290fb_fillrect(struct fb_info *info,
			       const struct fb_fillrect *rect)
{

	u32 x2, y2, vxres, vyres, height, width, fg;
	u32 cmd[7];

	vxres = info->var.xres_virtual;
	vyres = info->var.yres_virtual;

	if (!rect->width || !rect->height || rect->dx > vxres
	    || rect->dy > vyres)
		return;

	/* We could use hardware clipping but on many cards you get around
	 * hardware clipping by writing to framebuffer directly. */
	x2 = rect->dx + rect->width;
	y2 = rect->dy + rect->height;
	x2 = min(x2, vxres);
	y2 = min(y2, vyres);
	width = x2 - rect->dx;
	height = y2 - rect->dy;
	if (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	    info->fix.visual == FB_VISUAL_DIRECTCOLOR)
		fg = ((u32 *) (info->pseudo_palette))[rect->color];
	else
		fg = rect->color;

	switch (rect->rop) {

	case ROP_XOR:
		/* Set raster operation */
		cmd[1] = (2 << 7) | (GDC_ROP_XOR << 9);
		break;

	case ROP_COPY:
		/* Set raster operation */
		cmd[1] = (2 << 7) | (GDC_ROP_COPY << 9);
		break;

	}

	cmd[0] = (GDC_TYPE_SETREGISTER << 24) | (1 << 16) | GDC_REG_MODE_BITMAP;
	/* cmd[1] set earlier */
	cmd[2] =
	    (GDC_TYPE_SETCOLORREGISTER << 24) | (GDC_CMD_BODY_FORE_COLOR << 16);
	cmd[3] = fg;
	cmd[4] = (GDC_TYPE_DRAWRECTP << 24) | (GDC_CMD_BLT_FILL << 16);
	cmd[5] = (rect->dy << 16) | (rect->dx);
	cmd[6] = (height << 16) | width;

	mb862xxfb_write_fifo(7, cmd, info);
}