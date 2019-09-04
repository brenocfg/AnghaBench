#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fb_info {int dummy; } ;
struct fb_copyarea {int sx; int dx; int sy; int dy; int height; int width; } ;
typedef  int __u32 ;

/* Variables and functions */
 int GDC_CMD_BLTCOPY_BOTTOM_LEFT ; 
 int GDC_CMD_BLTCOPY_BOTTOM_RIGHT ; 
 int GDC_CMD_BLTCOPY_TOP_LEFT ; 
 int GDC_CMD_BLTCOPY_TOP_RIGHT ; 
 int GDC_REG_MODE_BITMAP ; 
 int GDC_ROP_COPY ; 
 int GDC_TYPE_BLTCOPYP ; 
 int GDC_TYPE_SETREGISTER ; 
 int /*<<< orphan*/  mb862xxfb_write_fifo (int,int*,struct fb_info*) ; 

__attribute__((used)) static void mb86290fb_copyarea(struct fb_info *info,
			       const struct fb_copyarea *area)
{
	__u32 cmd[6];

	cmd[0] = (GDC_TYPE_SETREGISTER << 24) | (1 << 16) | GDC_REG_MODE_BITMAP;
	/* Set raster operation */
	cmd[1] = (2 << 7) | (GDC_ROP_COPY << 9);
	cmd[2] = GDC_TYPE_BLTCOPYP << 24;

	if (area->sx >= area->dx && area->sy >= area->dy)
		cmd[2] |= GDC_CMD_BLTCOPY_TOP_LEFT << 16;
	else if (area->sx >= area->dx && area->sy <= area->dy)
		cmd[2] |= GDC_CMD_BLTCOPY_BOTTOM_LEFT << 16;
	else if (area->sx <= area->dx && area->sy >= area->dy)
		cmd[2] |= GDC_CMD_BLTCOPY_TOP_RIGHT << 16;
	else
		cmd[2] |= GDC_CMD_BLTCOPY_BOTTOM_RIGHT << 16;

	cmd[3] = (area->sy << 16) | area->sx;
	cmd[4] = (area->dy << 16) | area->dx;
	cmd[5] = (area->height << 16) | area->width;
	mb862xxfb_write_fifo(6, cmd, info);
}