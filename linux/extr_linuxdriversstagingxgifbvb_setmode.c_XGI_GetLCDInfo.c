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
struct vb_device_info {unsigned short LCDResInfo; unsigned short LCDInfo; int VBInfo; int VBType; TYPE_1__* LCDCapList; int /*<<< orphan*/  P3d4; scalar_t__ LCDTypeInfo; } ;
struct TYPE_4__ {unsigned short Ext_RESINFO; } ;
struct TYPE_3__ {unsigned short LCD_Capability; } ;

/* Variables and functions */
 int DriverMode ; 
 unsigned short EnableScalingLCD ; 
 unsigned short LCDNonExpanding ; 
 unsigned short LCDSyncBit ; 
 unsigned short PanelRef75Hz ; 
 unsigned short Panel_1024x768 ; 
 unsigned short Panel_1280x1024 ; 
 unsigned short Panel_1400x1050 ; 
 unsigned short ScalingLCD ; 
 int SetCRT2ToLCD ; 
 int SetInSlaveMode ; 
 unsigned short SetLCDDualLink ; 
 unsigned short SetLCDtoNonExpanding ; 
 int SetNotSimuMode ; 
 unsigned short SetPWDEnable ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 TYPE_2__* XGI330_EModeIDTable ; 
 unsigned short XGI_GetLCDCapPtr1 (struct vb_device_info*) ; 
 unsigned short XGI_LCDDualLink ; 
 unsigned short XGI_LCDVESATiming ; 
 int XGI_SetCRT2ToLCDA ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned char XGI_GetLCDInfo(unsigned short ModeIdIndex,
				    struct vb_device_info *pVBInfo)
{
	unsigned short temp, tempax, tempbx, resinfo = 0, LCDIdIndex;

	pVBInfo->LCDResInfo = 0;
	pVBInfo->LCDTypeInfo = 0;
	pVBInfo->LCDInfo = 0;

	/* si+Ext_ResInfo */
	resinfo = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;
	temp = xgifb_reg_get(pVBInfo->P3d4, 0x36); /* Get LCD Res.Info */
	tempbx = temp & 0x0F;

	if (tempbx == 0)
		tempbx = Panel_1024x768; /* default */

	/* LCD75 */
	if ((tempbx == Panel_1024x768) || (tempbx == Panel_1280x1024)) {
		if (pVBInfo->VBInfo & DriverMode) {
			tempax = xgifb_reg_get(pVBInfo->P3d4, 0x33);
			if (pVBInfo->VBInfo & XGI_SetCRT2ToLCDA)
				tempax &= 0x0F;
			else
				tempax >>= 4;

			if ((resinfo == 6) || (resinfo == 9)) {
				if (tempax >= 3)
					tempbx |= PanelRef75Hz;
			} else if ((resinfo == 7) || (resinfo == 8)) {
				if (tempax >= 4)
					tempbx |= PanelRef75Hz;
			}
		}
	}

	pVBInfo->LCDResInfo = tempbx;

	/* End of LCD75 */

	if (!(pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)))
		return 0;

	tempbx = 0;

	temp = xgifb_reg_get(pVBInfo->P3d4, 0x37);

	temp &= (ScalingLCD | LCDNonExpanding | LCDSyncBit | SetPWDEnable);

	tempbx |= temp;

	LCDIdIndex = XGI_GetLCDCapPtr1(pVBInfo);

	tempax = pVBInfo->LCDCapList[LCDIdIndex].LCD_Capability;

	if (((pVBInfo->VBType & VB_SIS302LV) ||
	     (pVBInfo->VBType & VB_XGI301C)) && (tempax & XGI_LCDDualLink))
		tempbx |= SetLCDDualLink;

	if ((pVBInfo->LCDResInfo == Panel_1400x1050) &&
	    (pVBInfo->VBInfo & SetCRT2ToLCD) && (resinfo == 9) &&
	    !(tempbx & EnableScalingLCD))
		/*
		 * set to center in 1280x1024 LCDB
		 * for Panel_1400x1050
		 */
		tempbx |= SetLCDtoNonExpanding;

	if (pVBInfo->VBInfo & SetInSlaveMode) {
		if (pVBInfo->VBInfo & SetNotSimuMode)
			tempbx |= XGI_LCDVESATiming;
	} else {
		tempbx |= XGI_LCDVESATiming;
	}

	pVBInfo->LCDInfo = tempbx;

	return 1;
}