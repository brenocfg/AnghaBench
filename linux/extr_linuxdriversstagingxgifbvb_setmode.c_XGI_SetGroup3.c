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
struct vb_device_info {int TVInfo; int VBInfo; int SetFlag; int VBType; int /*<<< orphan*/  Part3Port; } ;
struct TYPE_2__ {unsigned short Ext_ModeFlag; } ;

/* Variables and functions */
 unsigned short Charx8Dot ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToTV ; 
 int SetCRT2ToYPbPr525750 ; 
 int TVSetPAL ; 
 int TVSetPALM ; 
 int TVSetYPbPr525i ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int TVSimuMode ; 
 int VB_XGI301C ; 
 TYPE_1__* XGI330_EModeIDTable ; 
 unsigned char* XGI330_HiTVGroup3Data ; 
 unsigned char* XGI330_HiTVGroup3Simu ; 
 unsigned char* XGI330_HiTVGroup3Text ; 
 unsigned char* XGI330_Ren525pGroup3 ; 
 unsigned char* XGI330_Ren750pGroup3 ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,unsigned char const) ; 

__attribute__((used)) static void XGI_SetGroup3(unsigned short ModeIdIndex,
			  struct vb_device_info *pVBInfo)
{
	unsigned short i;
	unsigned char const *tempdi;
	unsigned short modeflag;

	/* si+Ext_ResInfo */
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	xgifb_reg_set(pVBInfo->Part3Port, 0x00, 0x00);
	if (pVBInfo->TVInfo & TVSetPAL) {
		xgifb_reg_set(pVBInfo->Part3Port, 0x13, 0xFA);
		xgifb_reg_set(pVBInfo->Part3Port, 0x14, 0xC8);
	} else {
		xgifb_reg_set(pVBInfo->Part3Port, 0x13, 0xF5);
		xgifb_reg_set(pVBInfo->Part3Port, 0x14, 0xB7);
	}

	if (!(pVBInfo->VBInfo & SetCRT2ToTV))
		return;

	if (pVBInfo->TVInfo & TVSetPALM) {
		xgifb_reg_set(pVBInfo->Part3Port, 0x13, 0xFA);
		xgifb_reg_set(pVBInfo->Part3Port, 0x14, 0xC8);
		xgifb_reg_set(pVBInfo->Part3Port, 0x3D, 0xA8);
	}

	if ((pVBInfo->VBInfo & SetCRT2ToHiVision) || (pVBInfo->VBInfo
			& SetCRT2ToYPbPr525750)) {
		if (pVBInfo->TVInfo & TVSetYPbPr525i)
			return;

		tempdi = XGI330_HiTVGroup3Data;
		if (pVBInfo->SetFlag & TVSimuMode) {
			tempdi = XGI330_HiTVGroup3Simu;
			if (!(modeflag & Charx8Dot))
				tempdi = XGI330_HiTVGroup3Text;
		}

		if (pVBInfo->TVInfo & TVSetYPbPr525p)
			tempdi = XGI330_Ren525pGroup3;

		if (pVBInfo->TVInfo & TVSetYPbPr750p)
			tempdi = XGI330_Ren750pGroup3;

		for (i = 0; i <= 0x3E; i++)
			xgifb_reg_set(pVBInfo->Part3Port, i, tempdi[i]);

		if (pVBInfo->VBType & VB_XGI301C) { /* Marcovision */
			if (pVBInfo->TVInfo & TVSetYPbPr525p)
				xgifb_reg_set(pVBInfo->Part3Port, 0x28, 0x3f);
		}
	}
}