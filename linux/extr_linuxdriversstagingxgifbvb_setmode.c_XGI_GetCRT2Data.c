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
struct vb_device_info {int NewFlickerMode; int RVBHRS; int VBInfo; unsigned short HT; unsigned short VT; scalar_t__ LCDResInfo; int LCDInfo; int VGAVDE; unsigned short VGAHDE; unsigned short HDE; unsigned short VDE; int TVInfo; int /*<<< orphan*/  VGAVT; int /*<<< orphan*/  VGAHT; int /*<<< orphan*/  RVBHCFACT; int /*<<< orphan*/  RVBHCMAX; } ;
struct SiS_TVData {unsigned short TVHDE; unsigned short TVVDE; int RVBHRS; int FlickerMode; int /*<<< orphan*/  VGAVT; int /*<<< orphan*/  VGAHT; int /*<<< orphan*/  RVBHCFACT; int /*<<< orphan*/  RVBHCMAX; } ;
struct SiS_LCDData {unsigned short LCDHT; unsigned short LCDVT; int /*<<< orphan*/  VGAVT; int /*<<< orphan*/  VGAHT; int /*<<< orphan*/  RVBHCFACT; int /*<<< orphan*/  RVBHCMAX; } ;
struct TYPE_2__ {unsigned short Ext_ModeFlag; unsigned short Ext_RESINFO; } ;

/* Variables and functions */
 unsigned short Charx8Dot ; 
 unsigned short ExtHiTVHT ; 
 unsigned short ExtHiTVVT ; 
 int LCDNonExpanding ; 
 int NTSC1024x768 ; 
 unsigned short NTSC1024x768HT ; 
 unsigned short NTSCHT ; 
 unsigned short NTSCVT ; 
 unsigned short PALHT ; 
 unsigned short PALVT ; 
 scalar_t__ Panel_1024x768 ; 
 scalar_t__ Panel_1024x768x75 ; 
 scalar_t__ Panel_1280x1024 ; 
 scalar_t__ Panel_1280x1024x75 ; 
 scalar_t__ Panel_1280x960 ; 
 scalar_t__ Panel_1400x1050 ; 
 scalar_t__ Panel_1600x1200 ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToRAMDAC ; 
 int SetCRT2ToTV ; 
 int SetCRT2ToYPbPr525750 ; 
 int SetInSlaveMode ; 
 unsigned short StHiTVHT ; 
 unsigned short StHiTVVT ; 
 unsigned short StHiTextTVHT ; 
 unsigned short StHiTextTVVT ; 
 int TVSetPAL ; 
 int TVSetYPbPr525i ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int TVSimuMode ; 
 TYPE_1__* XGI330_EModeIDTable ; 
 struct SiS_LCDData* XGI_GetLcdPtr (int /*<<< orphan*/ ,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_GetRAMDAC2DATA (unsigned short,unsigned short,struct vb_device_info*) ; 
 struct SiS_TVData* XGI_GetTVPtr (unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_LCDDataTable ; 
 int XGI_LCDVESATiming ; 
 int XGI_SetCRT2ToLCDA ; 
 unsigned short YPbPrTV525iHT ; 
 unsigned short YPbPrTV525iVT ; 
 unsigned short YPbPrTV525pHT ; 
 unsigned short YPbPrTV525pVT ; 
 unsigned short YPbPrTV750pHT ; 
 unsigned short YPbPrTV750pVT ; 

__attribute__((used)) static void XGI_GetCRT2Data(unsigned short ModeIdIndex,
			    unsigned short RefreshRateTableIndex,
			    struct vb_device_info *pVBInfo)
{
	unsigned short tempax = 0, tempbx = 0, modeflag, resinfo;

	struct SiS_LCDData const *LCDPtr = NULL;

	/* si+Ext_ResInfo */
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	resinfo = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;
	pVBInfo->NewFlickerMode = 0;
	pVBInfo->RVBHRS = 50;

	if (pVBInfo->VBInfo & SetCRT2ToRAMDAC) {
		XGI_GetRAMDAC2DATA(ModeIdIndex, RefreshRateTableIndex, pVBInfo);
		return;
	}

	if (pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)) {
		LCDPtr = XGI_GetLcdPtr(XGI_LCDDataTable, ModeIdIndex,
				       pVBInfo);

		pVBInfo->RVBHCMAX = LCDPtr->RVBHCMAX;
		pVBInfo->RVBHCFACT = LCDPtr->RVBHCFACT;
		pVBInfo->VGAHT = LCDPtr->VGAHT;
		pVBInfo->VGAVT = LCDPtr->VGAVT;
		pVBInfo->HT = LCDPtr->LCDHT;
		pVBInfo->VT = LCDPtr->LCDVT;

		if (pVBInfo->LCDResInfo == Panel_1024x768) {
			tempax = 1024;
			tempbx = 768;

			if (!(pVBInfo->LCDInfo & XGI_LCDVESATiming)) {
				if (pVBInfo->VGAVDE == 357)
					tempbx = 527;
				else if (pVBInfo->VGAVDE == 420)
					tempbx = 620;
				else if (pVBInfo->VGAVDE == 525)
					tempbx = 775;
				else if (pVBInfo->VGAVDE == 600)
					tempbx = 775;
			}
		} else if (pVBInfo->LCDResInfo == Panel_1024x768x75) {
			tempax = 1024;
			tempbx = 768;
		} else if (pVBInfo->LCDResInfo == Panel_1280x1024) {
			tempax = 1280;
			if (pVBInfo->VGAVDE == 360)
				tempbx = 768;
			else if (pVBInfo->VGAVDE == 375)
				tempbx = 800;
			else if (pVBInfo->VGAVDE == 405)
				tempbx = 864;
			else
				tempbx = 1024;
		} else if (pVBInfo->LCDResInfo == Panel_1280x1024x75) {
			tempax = 1280;
			tempbx = 1024;
		} else if (pVBInfo->LCDResInfo == Panel_1280x960) {
			tempax = 1280;
			if (pVBInfo->VGAVDE == 350)
				tempbx = 700;
			else if (pVBInfo->VGAVDE == 400)
				tempbx = 800;
			else if (pVBInfo->VGAVDE == 1024)
				tempbx = 960;
			else
				tempbx = 960;
		} else if (pVBInfo->LCDResInfo == Panel_1400x1050) {
			tempax = 1400;
			tempbx = 1050;

			if (pVBInfo->VGAVDE == 1024) {
				tempax = 1280;
				tempbx = 1024;
			}
		} else if (pVBInfo->LCDResInfo == Panel_1600x1200) {
			tempax = 1600;
			tempbx = 1200; /* alan 10/14/2003 */
			if (!(pVBInfo->LCDInfo & XGI_LCDVESATiming)) {
				if (pVBInfo->VGAVDE == 350)
					tempbx = 875;
				else if (pVBInfo->VGAVDE == 400)
					tempbx = 1000;
			}
		}

		if (pVBInfo->LCDInfo & LCDNonExpanding) {
			tempax = pVBInfo->VGAHDE;
			tempbx = pVBInfo->VGAVDE;
		}

		pVBInfo->HDE = tempax;
		pVBInfo->VDE = tempbx;
		return;
	}

	if (pVBInfo->VBInfo & (SetCRT2ToTV)) {
		struct SiS_TVData const *TVPtr;

		TVPtr = XGI_GetTVPtr(ModeIdIndex, RefreshRateTableIndex,
				     pVBInfo);

		pVBInfo->RVBHCMAX = TVPtr->RVBHCMAX;
		pVBInfo->RVBHCFACT = TVPtr->RVBHCFACT;
		pVBInfo->VGAHT = TVPtr->VGAHT;
		pVBInfo->VGAVT = TVPtr->VGAVT;
		pVBInfo->HDE = TVPtr->TVHDE;
		pVBInfo->VDE = TVPtr->TVVDE;
		pVBInfo->RVBHRS = TVPtr->RVBHRS;
		pVBInfo->NewFlickerMode = TVPtr->FlickerMode;

		if (pVBInfo->VBInfo & SetCRT2ToHiVision) {
			if (resinfo == 0x08)
				pVBInfo->NewFlickerMode = 0x40;
			else if (resinfo == 0x09)
				pVBInfo->NewFlickerMode = 0x40;
			else if (resinfo == 0x12)
				pVBInfo->NewFlickerMode = 0x40;

			if (pVBInfo->VGAVDE == 350)
				pVBInfo->TVInfo |= TVSimuMode;

			tempax = ExtHiTVHT;
			tempbx = ExtHiTVVT;

			if (pVBInfo->VBInfo & SetInSlaveMode) {
				if (pVBInfo->TVInfo & TVSimuMode) {
					tempax = StHiTVHT;
					tempbx = StHiTVVT;

					if (!(modeflag & Charx8Dot)) {
						tempax = StHiTextTVHT;
						tempbx = StHiTextTVVT;
					}
				}
			}
		} else if (pVBInfo->VBInfo & SetCRT2ToYPbPr525750) {
			if (pVBInfo->TVInfo & TVSetYPbPr750p) {
				tempax = YPbPrTV750pHT; /* Ext750pTVHT */
				tempbx = YPbPrTV750pVT; /* Ext750pTVVT */
			}

			if (pVBInfo->TVInfo & TVSetYPbPr525p) {
				tempax = YPbPrTV525pHT; /* Ext525pTVHT */
				tempbx = YPbPrTV525pVT; /* Ext525pTVVT */
			} else if (pVBInfo->TVInfo & TVSetYPbPr525i) {
				tempax = YPbPrTV525iHT; /* Ext525iTVHT */
				tempbx = YPbPrTV525iVT; /* Ext525iTVVT */
				if (pVBInfo->TVInfo & NTSC1024x768)
					tempax = NTSC1024x768HT;
			}
		} else {
			tempax = PALHT;
			tempbx = PALVT;
			if (!(pVBInfo->TVInfo & TVSetPAL)) {
				tempax = NTSCHT;
				tempbx = NTSCVT;
				if (pVBInfo->TVInfo & NTSC1024x768)
					tempax = NTSC1024x768HT;
			}
		}

		pVBInfo->HT = tempax;
		pVBInfo->VT = tempbx;
	}
}