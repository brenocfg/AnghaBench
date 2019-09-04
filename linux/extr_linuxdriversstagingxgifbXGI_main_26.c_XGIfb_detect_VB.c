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
struct xgifb_video_info {int TV_plug; scalar_t__ TV_type; int /*<<< orphan*/  display2; int /*<<< orphan*/  display2_force; struct vb_device_info dev_info; } ;

/* Variables and functions */
 int IND_XGI_SCRATCH_REG_CR32 ; 
 int SIS_CRT1 ; 
 int SIS_VB_COMPOSITE ; 
 int SIS_VB_CRT2 ; 
 int SIS_VB_HIVISION ; 
 int SIS_VB_LCD ; 
 int SIS_VB_SCART ; 
 int SIS_VB_SVIDEO ; 
 int SIS_VB_TV ; 
 scalar_t__ TVMODE_HIVISION ; 
 scalar_t__ TVMODE_NTSC ; 
 scalar_t__ TVMODE_PAL ; 
 int TVPLUG_COMPOSITE ; 
 int TVPLUG_SCART ; 
 void* TVPLUG_SVIDEO ; 
 int /*<<< orphan*/  XGIFB_DISP_CRT ; 
 int /*<<< orphan*/  XGIFB_DISP_LCD ; 
 int /*<<< orphan*/  XGIFB_DISP_NONE ; 
 int /*<<< orphan*/  XGIFB_DISP_TV ; 
 int XGIfb_crt1off ; 
 int XGIfb_forcecrt1 ; 
 int XGIfb_tvplug ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void XGIfb_detect_VB(struct xgifb_video_info *xgifb_info)
{
	struct vb_device_info *vb = &xgifb_info->dev_info;
	u8 cr32, temp = 0;

	xgifb_info->TV_plug = 0;
	xgifb_info->TV_type = 0;

	cr32 = xgifb_reg_get(vb->P3d4, IND_XGI_SCRATCH_REG_CR32);

	if ((cr32 & SIS_CRT1) && !XGIfb_crt1off) {
		XGIfb_crt1off = 0;
	} else {
		if (cr32 & 0x5F)
			XGIfb_crt1off = 1;
		else
			XGIfb_crt1off = 0;
	}

	if (!xgifb_info->display2_force) {
		if (cr32 & SIS_VB_TV)
			xgifb_info->display2 = XGIFB_DISP_TV;
		else if (cr32 & SIS_VB_LCD)
			xgifb_info->display2 = XGIFB_DISP_LCD;
		else if (cr32 & SIS_VB_CRT2)
			xgifb_info->display2 = XGIFB_DISP_CRT;
		else
			xgifb_info->display2 = XGIFB_DISP_NONE;
	}

	if (XGIfb_tvplug != -1) {
		/* Override with option */
		xgifb_info->TV_plug = XGIfb_tvplug;
	} else if (cr32 & SIS_VB_HIVISION) {
		xgifb_info->TV_type = TVMODE_HIVISION;
		xgifb_info->TV_plug = TVPLUG_SVIDEO;
	} else if (cr32 & SIS_VB_SVIDEO) {
		xgifb_info->TV_plug = TVPLUG_SVIDEO;
	} else if (cr32 & SIS_VB_COMPOSITE) {
		xgifb_info->TV_plug = TVPLUG_COMPOSITE;
	} else if (cr32 & SIS_VB_SCART) {
		xgifb_info->TV_plug = TVPLUG_SCART;
	}

	if (xgifb_info->TV_type == 0) {
		temp = xgifb_reg_get(vb->P3d4, 0x38);
		if (temp & 0x10)
			xgifb_info->TV_type = TVMODE_PAL;
		else
			xgifb_info->TV_type = TVMODE_NTSC;
	}

	/* Copy forceCRT1 option to CRT1off if option is given */
	if (XGIfb_forcecrt1 != -1) {
		if (XGIfb_forcecrt1)
			XGIfb_crt1off = 0;
		else
			XGIfb_crt1off = 1;
	}
}