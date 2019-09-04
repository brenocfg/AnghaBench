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
struct vb_device_info {int VBInfo; int LCDInfo; scalar_t__ LCDResInfo; int HDE; int VDE; int /*<<< orphan*/  VT; int /*<<< orphan*/  HT; int /*<<< orphan*/  VGAVT; int /*<<< orphan*/  VGAHT; } ;
struct SiS_LVDSData {int /*<<< orphan*/  LCDVT; int /*<<< orphan*/  LCDHT; int /*<<< orphan*/  VGAVT; int /*<<< orphan*/  VGAHT; } ;

/* Variables and functions */
 int EnableScalingLCD ; 
 scalar_t__ Panel_1024x768 ; 
 scalar_t__ Panel_1024x768x75 ; 
 scalar_t__ Panel_1280x1024 ; 
 scalar_t__ Panel_1280x1024x75 ; 
 scalar_t__ Panel_1400x1050 ; 
 int SetCRT2ToLCD ; 
 int SetLCDtoNonExpanding ; 
 int /*<<< orphan*/  XGI_EPLLCDDataPtr ; 
 struct SiS_LVDSData* XGI_GetLcdPtr (int /*<<< orphan*/ ,unsigned short,struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 

__attribute__((used)) static void XGI_GetLVDSData(unsigned short ModeIdIndex,
			    struct vb_device_info *pVBInfo)
{
	struct SiS_LVDSData const *LCDPtr;

	if (!(pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)))
		return;

	LCDPtr = XGI_GetLcdPtr(XGI_EPLLCDDataPtr, ModeIdIndex, pVBInfo);
	pVBInfo->VGAHT	= LCDPtr->VGAHT;
	pVBInfo->VGAVT	= LCDPtr->VGAVT;
	pVBInfo->HT	= LCDPtr->LCDHT;
	pVBInfo->VT	= LCDPtr->LCDVT;

	if (pVBInfo->LCDInfo & (SetLCDtoNonExpanding | EnableScalingLCD))
		return;

	if ((pVBInfo->LCDResInfo == Panel_1024x768) ||
	    (pVBInfo->LCDResInfo == Panel_1024x768x75)) {
		pVBInfo->HDE = 1024;
		pVBInfo->VDE = 768;
	} else if ((pVBInfo->LCDResInfo == Panel_1280x1024) ||
		   (pVBInfo->LCDResInfo == Panel_1280x1024x75)) {
		pVBInfo->HDE = 1280;
		pVBInfo->VDE = 1024;
	} else if (pVBInfo->LCDResInfo == Panel_1400x1050) {
		pVBInfo->HDE = 1400;
		pVBInfo->VDE = 1050;
	} else {
		pVBInfo->HDE = 1600;
		pVBInfo->VDE = 1200;
	}
}