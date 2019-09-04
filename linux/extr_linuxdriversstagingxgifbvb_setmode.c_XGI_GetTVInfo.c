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
struct vb_device_info {int VBInfo; int VBType; unsigned short TVInfo; int /*<<< orphan*/  P3d4; } ;
struct TYPE_2__ {unsigned short Ext_ModeFlag; unsigned short Ext_RESINFO; } ;

/* Variables and functions */
 unsigned short NTSC1024x768 ; 
 unsigned short RPLLDIV2XO ; 
 unsigned short SetCHTVOverScan ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToSCART ; 
 int SetCRT2ToTV ; 
 int SetCRT2ToYPbPr525750 ; 
 int SetInSlaveMode ; 
 int SetNotSimuMode ; 
 unsigned short TVSetHiVision ; 
 unsigned short TVSetNTSCJ ; 
 unsigned short TVSetPAL ; 
 unsigned short TVSetPALM ; 
 unsigned short TVSetPALN ; 
 unsigned short TVSetYPbPr525i ; 
 unsigned short TVSetYPbPr525p ; 
 unsigned short TVSetYPbPr750p ; 
 unsigned short TVSimuMode ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 TYPE_1__* XGI330_EModeIDTable ; 
 unsigned short YPbPrMode ; 
 unsigned short YPbPrMode525i ; 
 unsigned short YPbPrMode525p ; 
 unsigned short YPbPrMode750p ; 
 unsigned short xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void XGI_GetTVInfo(unsigned short ModeIdIndex,
			  struct vb_device_info *pVBInfo)
{
	unsigned short tempbx = 0, resinfo = 0, modeflag, index1;

	if (pVBInfo->VBInfo & SetCRT2ToTV) {
		modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
		resinfo = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;

		tempbx = xgifb_reg_get(pVBInfo->P3d4, 0x35);
		if (tempbx & TVSetPAL) {
			tempbx &= (SetCHTVOverScan |
				   TVSetPALM |
				   TVSetPALN |
				   TVSetPAL);
			if (tempbx & TVSetPALM)
				/* set to NTSC if PAL-M */
				tempbx &= ~TVSetPAL;
		} else {
			tempbx &= (SetCHTVOverScan |
				   TVSetNTSCJ |
				   TVSetPAL);
		}

		if (pVBInfo->VBInfo & SetCRT2ToSCART)
			tempbx |= TVSetPAL;

		if (pVBInfo->VBInfo & SetCRT2ToYPbPr525750) {
			index1 = xgifb_reg_get(pVBInfo->P3d4, 0x35);
			index1 &= YPbPrMode;

			if (index1 == YPbPrMode525i)
				tempbx |= TVSetYPbPr525i;

			if (index1 == YPbPrMode525p)
				tempbx = tempbx | TVSetYPbPr525p;
			if (index1 == YPbPrMode750p)
				tempbx = tempbx | TVSetYPbPr750p;
		}

		if (pVBInfo->VBInfo & SetCRT2ToHiVision)
			tempbx = tempbx | TVSetHiVision | TVSetPAL;

		if ((pVBInfo->VBInfo & SetInSlaveMode) &&
		    (!(pVBInfo->VBInfo & SetNotSimuMode)))
			tempbx |= TVSimuMode;

		if (!(tempbx & TVSetPAL) && (modeflag > 13) && (resinfo == 8)) {
			/* NTSC 1024x768, */
			tempbx |= NTSC1024x768;
		}

		tempbx |= RPLLDIV2XO;

		if (pVBInfo->VBInfo & SetCRT2ToHiVision) {
			if (pVBInfo->VBInfo & SetInSlaveMode)
				tempbx &= (~RPLLDIV2XO);
		} else if (tempbx & (TVSetYPbPr525p | TVSetYPbPr750p)) {
			tempbx &= (~RPLLDIV2XO);
		} else if (!(pVBInfo->VBType & (VB_SIS301B | VB_SIS302B |
						VB_SIS301LV | VB_SIS302LV |
						VB_XGI301C))) {
			if (tempbx & TVSimuMode)
				tempbx &= (~RPLLDIV2XO);
		}
	}
	pVBInfo->TVInfo = tempbx;
}