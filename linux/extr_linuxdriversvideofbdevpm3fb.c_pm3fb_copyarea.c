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
struct pm3_par {int dummy; } ;
struct TYPE_2__ {scalar_t__ xres_virtual; scalar_t__ yres_virtual; } ;
struct fb_info {scalar_t__ state; int flags; TYPE_1__ var; struct pm3_par* par; } ;
struct fb_copyarea {scalar_t__ width; scalar_t__ height; scalar_t__ sx; scalar_t__ sy; scalar_t__ dx; scalar_t__ dy; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  PM3Config2D ; 
 int PM3Config2D_Blocking ; 
 int PM3Config2D_FBWriteEnable ; 
 int PM3Config2D_ForegroundROP (int) ; 
 int PM3Config2D_ForegroundROPEnable ; 
 int PM3Config2D_UserScissorEnable ; 
 int /*<<< orphan*/  PM3FBSourceReadBufferOffset ; 
 int PM3FBSourceReadBufferOffset_XOffset (int) ; 
 int PM3FBSourceReadBufferOffset_YOffset (int) ; 
 int /*<<< orphan*/  PM3RectanglePosition ; 
 int PM3RectanglePosition_XOffset (int) ; 
 int PM3RectanglePosition_YOffset (int) ; 
 int /*<<< orphan*/  PM3Render2D ; 
 int PM3Render2D_FBSourceReadEnable ; 
 int PM3Render2D_Height (int) ; 
 int PM3Render2D_Operation_Normal ; 
 int PM3Render2D_SpanOperation ; 
 int PM3Render2D_Width (int) ; 
 int PM3Render2D_XPositive ; 
 int PM3Render2D_YPositive ; 
 int /*<<< orphan*/  PM3ScissorMaxXY ; 
 int /*<<< orphan*/  PM3ScissorMinXY ; 
 int /*<<< orphan*/  PM3_WAIT (struct pm3_par*,int) ; 
 int /*<<< orphan*/  PM3_WRITE_REG (struct pm3_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  memcpy (struct fb_copyarea*,struct fb_copyarea const*,int) ; 

__attribute__((used)) static void pm3fb_copyarea(struct fb_info *info,
				const struct fb_copyarea *area)
{
	struct pm3_par *par = info->par;
	struct fb_copyarea modded;
	u32 vxres, vyres;
	int x_align, o_x, o_y;

	if (info->state != FBINFO_STATE_RUNNING)
		return;
	if (info->flags & FBINFO_HWACCEL_DISABLED) {
		cfb_copyarea(info, area);
		return;
	}

	memcpy(&modded, area, sizeof(struct fb_copyarea));

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

	o_x = modded.sx - modded.dx;	/*(sx > dx ) ? (sx - dx) : (dx - sx); */
	o_y = modded.sy - modded.dy;	/*(sy > dy ) ? (sy - dy) : (dy - sy); */

	x_align = (modded.sx & 0x1f);

	PM3_WAIT(par, 6);

	PM3_WRITE_REG(par, PM3Config2D,
			PM3Config2D_UserScissorEnable |
			PM3Config2D_ForegroundROPEnable |
			PM3Config2D_Blocking |
			PM3Config2D_ForegroundROP(0x3) | /* Ox3 is GXcopy */
			PM3Config2D_FBWriteEnable);

	PM3_WRITE_REG(par, PM3ScissorMinXY,
			((modded.dy & 0x0fff) << 16) | (modded.dx & 0x0fff));
	PM3_WRITE_REG(par, PM3ScissorMaxXY,
			(((modded.dy + modded.height) & 0x0fff) << 16) |
			((modded.dx + modded.width) & 0x0fff));

	PM3_WRITE_REG(par, PM3FBSourceReadBufferOffset,
			PM3FBSourceReadBufferOffset_XOffset(o_x) |
			PM3FBSourceReadBufferOffset_YOffset(o_y));

	PM3_WRITE_REG(par, PM3RectanglePosition,
			PM3RectanglePosition_XOffset(modded.dx - x_align) |
			PM3RectanglePosition_YOffset(modded.dy));

	PM3_WRITE_REG(par, PM3Render2D,
			((modded.sx > modded.dx) ? PM3Render2D_XPositive : 0) |
			((modded.sy > modded.dy) ? PM3Render2D_YPositive : 0) |
			PM3Render2D_Operation_Normal |
			PM3Render2D_SpanOperation |
			PM3Render2D_FBSourceReadEnable |
			PM3Render2D_Width(modded.width + x_align) |
			PM3Render2D_Height(modded.height));
}