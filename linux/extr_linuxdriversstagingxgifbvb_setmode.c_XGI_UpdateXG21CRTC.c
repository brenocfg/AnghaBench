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
struct vb_device_info {int /*<<< orphan*/  P3d4; } ;
struct TYPE_4__ {scalar_t__ Ext_CRT1CRTC; } ;
struct TYPE_3__ {int /*<<< orphan*/  CR16; int /*<<< orphan*/  CR15; int /*<<< orphan*/  CR03; int /*<<< orphan*/  CR02; } ;

/* Variables and functions */
 scalar_t__ RES640x480x60 ; 
 scalar_t__ RES640x480x72 ; 
 TYPE_2__* XGI330_RefIndex ; 
 TYPE_1__* XGI_UpdateCRT1Table ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGI_UpdateXG21CRTC(unsigned short ModeNo,
			       struct vb_device_info *pVBInfo,
			       unsigned short RefreshRateTableIndex)
{
	int index = -1;

	xgifb_reg_and(pVBInfo->P3d4, 0x11, 0x7F); /* Unlock CR0~7 */
	if (ModeNo == 0x2E &&
	    (XGI330_RefIndex[RefreshRateTableIndex].Ext_CRT1CRTC ==
						      RES640x480x60))
		index = 12;
	else if (ModeNo == 0x2E && (XGI330_RefIndex[RefreshRateTableIndex].
				Ext_CRT1CRTC == RES640x480x72))
		index = 13;
	else if (ModeNo == 0x2F)
		index = 14;
	else if (ModeNo == 0x50)
		index = 15;
	else if (ModeNo == 0x59)
		index = 16;

	if (index != -1) {
		xgifb_reg_set(pVBInfo->P3d4, 0x02,
			      XGI_UpdateCRT1Table[index].CR02);
		xgifb_reg_set(pVBInfo->P3d4, 0x03,
			      XGI_UpdateCRT1Table[index].CR03);
		xgifb_reg_set(pVBInfo->P3d4, 0x15,
			      XGI_UpdateCRT1Table[index].CR15);
		xgifb_reg_set(pVBInfo->P3d4, 0x16,
			      XGI_UpdateCRT1Table[index].CR16);
	}
}