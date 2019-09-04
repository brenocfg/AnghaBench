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
struct vb_device_info {int /*<<< orphan*/  Part1Port; int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; } ;
struct xgifb_video_info {scalar_t__ display2; struct vb_device_info dev_info; } ;
struct fb_var_screeninfo {unsigned int yoffset; unsigned int xoffset; } ;
struct TYPE_2__ {unsigned int xres_virtual; int bits_per_pixel; } ;
struct fb_info {TYPE_1__ var; struct xgifb_video_info* par; } ;

/* Variables and functions */
 int IND_SIS_PASSWORD ; 
 int /*<<< orphan*/  SIS_CRT2_WENABLE_315 ; 
 unsigned int SIS_PASSWORD ; 
 scalar_t__ XGIFB_DISP_NONE ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int XGIfb_pan_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct xgifb_video_info *xgifb_info = info->par;
	struct vb_device_info *vb = &xgifb_info->dev_info;
	unsigned int base;

	base = var->yoffset * info->var.xres_virtual + var->xoffset;

	/* calculate base bpp dep. */
	switch (info->var.bits_per_pixel) {
	case 16:
		base >>= 1;
		break;
	case 32:
		break;
	case 8:
	default:
		base >>= 2;
		break;
	}

	xgifb_reg_set(vb->P3c4, IND_SIS_PASSWORD, SIS_PASSWORD);

	xgifb_reg_set(vb->P3d4, 0x0D, base & 0xFF);
	xgifb_reg_set(vb->P3d4, 0x0C, (base >> 8) & 0xFF);
	xgifb_reg_set(vb->P3c4, 0x0D, (base >> 16) & 0xFF);
	xgifb_reg_set(vb->P3c4, 0x37, (base >> 24) & 0x03);
	xgifb_reg_and_or(vb->P3c4, 0x37, 0xDF, (base >> 21) & 0x04);

	if (xgifb_info->display2 != XGIFB_DISP_NONE) {
		xgifb_reg_or(vb->Part1Port, SIS_CRT2_WENABLE_315, 0x01);
		xgifb_reg_set(vb->Part1Port, 0x06, (base & 0xFF));
		xgifb_reg_set(vb->Part1Port, 0x05, ((base >> 8) & 0xFF));
		xgifb_reg_set(vb->Part1Port, 0x04, ((base >> 16) & 0xFF));
		xgifb_reg_and_or(vb->Part1Port, 0x02, 0x7F,
				 ((base >> 24) & 0x01) << 7);
	}
	return 0;
}