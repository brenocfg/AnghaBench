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
typedef  int u8 ;
struct vb_device_info {int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; } ;
struct xgifb_video_info {struct vb_device_info dev_info; } ;
struct fb_info {struct xgifb_video_info* par; } ;

/* Variables and functions */
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int XGIfb_blank(int blank, struct fb_info *info)
{
	struct xgifb_video_info *xgifb_info = info->par;
	struct vb_device_info *vb = &xgifb_info->dev_info;
	u8 reg;

	reg = xgifb_reg_get(vb->P3d4, 0x17);

	if (blank > 0)
		reg &= 0x7f;
	else
		reg |= 0x80;

	xgifb_reg_set(vb->P3d4, 0x17, reg);
	xgifb_reg_set(vb->P3c4, 0x00, 0x01); /* Synchronous Reset */
	xgifb_reg_set(vb->P3c4, 0x00, 0x03); /* End Reset */
	return 0;
}