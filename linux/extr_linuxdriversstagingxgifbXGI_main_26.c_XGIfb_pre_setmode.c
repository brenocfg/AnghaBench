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
struct vb_device_info {int /*<<< orphan*/  P3d4; } ;
struct xgifb_video_info {int display2; int rate_idx; int /*<<< orphan*/  TV_type; int /*<<< orphan*/  TV_plug; struct vb_device_info dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IND_XGI_SCRATCH_REG_CR30 ; 
 int /*<<< orphan*/  IND_XGI_SCRATCH_REG_CR31 ; 
 int /*<<< orphan*/  IND_XGI_SCRATCH_REG_CR33 ; 
 int SIS_DRIVER_MODE ; 
 int SIS_SIMULTANEOUS_VIEW_ENABLE ; 
 int SIS_VB_OUTPUT_COMPOSITE ; 
 int SIS_VB_OUTPUT_CRT2 ; 
 int SIS_VB_OUTPUT_DISABLE ; 
 int SIS_VB_OUTPUT_HIVISION ; 
 int SIS_VB_OUTPUT_LCD ; 
 int SIS_VB_OUTPUT_SCART ; 
 int SIS_VB_OUTPUT_SVIDEO ; 
 int /*<<< orphan*/  TVMODE_HIVISION ; 
 int /*<<< orphan*/  TVMODE_PAL ; 
 int /*<<< orphan*/  TVPLUG_COMPOSITE ; 
 int /*<<< orphan*/  TVPLUG_SCART ; 
 int /*<<< orphan*/  TVPLUG_SVIDEO ; 
#define  XGIFB_DISP_CRT 130 
#define  XGIFB_DISP_LCD 129 
#define  XGIFB_DISP_TV 128 
 int XGIfb_tvmode ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void XGIfb_pre_setmode(struct xgifb_video_info *xgifb_info)
{
	struct vb_device_info *vb = &xgifb_info->dev_info;
	u8 cr30 = 0, cr31 = 0;

	cr31 = xgifb_reg_get(vb->P3d4, 0x31);
	cr31 &= ~0x60;

	switch (xgifb_info->display2) {
	case XGIFB_DISP_CRT:
		cr30 = SIS_VB_OUTPUT_CRT2 | SIS_SIMULTANEOUS_VIEW_ENABLE;
		cr31 |= SIS_DRIVER_MODE;
		break;
	case XGIFB_DISP_LCD:
		cr30 = SIS_VB_OUTPUT_LCD | SIS_SIMULTANEOUS_VIEW_ENABLE;
		cr31 |= SIS_DRIVER_MODE;
		break;
	case XGIFB_DISP_TV:
		if (xgifb_info->TV_type == TVMODE_HIVISION)
			cr30 = SIS_VB_OUTPUT_HIVISION
					| SIS_SIMULTANEOUS_VIEW_ENABLE;
		else if (xgifb_info->TV_plug == TVPLUG_SVIDEO)
			cr30 = SIS_VB_OUTPUT_SVIDEO
					| SIS_SIMULTANEOUS_VIEW_ENABLE;
		else if (xgifb_info->TV_plug == TVPLUG_COMPOSITE)
			cr30 = SIS_VB_OUTPUT_COMPOSITE
					| SIS_SIMULTANEOUS_VIEW_ENABLE;
		else if (xgifb_info->TV_plug == TVPLUG_SCART)
			cr30 = SIS_VB_OUTPUT_SCART
					| SIS_SIMULTANEOUS_VIEW_ENABLE;
		cr31 |= SIS_DRIVER_MODE;

		if (XGIfb_tvmode == 1 || xgifb_info->TV_type == TVMODE_PAL)
			cr31 |= 0x01;
		else
			cr31 &= ~0x01;
		break;
	default: /* disable CRT2 */
		cr30 = 0x00;
		cr31 |= (SIS_DRIVER_MODE | SIS_VB_OUTPUT_DISABLE);
	}

	xgifb_reg_set(vb->P3d4, IND_XGI_SCRATCH_REG_CR30, cr30);
	xgifb_reg_set(vb->P3d4, IND_XGI_SCRATCH_REG_CR31, cr31);
	xgifb_reg_set(vb->P3d4, IND_XGI_SCRATCH_REG_CR33,
		      (xgifb_info->rate_idx & 0x0F));
}