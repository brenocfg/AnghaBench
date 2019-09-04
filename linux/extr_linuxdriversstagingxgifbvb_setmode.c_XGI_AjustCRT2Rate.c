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
struct vb_device_info {int VBInfo; int VBType; scalar_t__ LCDResInfo; int LCDInfo; int SetFlag; } ;
struct TYPE_4__ {unsigned short Ext_ModeFlag; unsigned short Ext_RESINFO; } ;
struct TYPE_3__ {unsigned short ModeID; unsigned short Ext_InfoFlag; } ;

/* Variables and functions */
 int LCDNonExpanding ; 
 unsigned short NoSupportSimuTV ; 
 scalar_t__ Panel_1280x1024 ; 
 scalar_t__ Panel_1280x960 ; 
 int SetCRT2ToAVIDEO ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToRAMDAC ; 
 int SetCRT2ToSCART ; 
 int SetCRT2ToSVIDEO ; 
 int SetCRT2ToYPbPr525750 ; 
 int SetInSlaveMode ; 
 int SetNotSimuMode ; 
 unsigned short SupportCRT2in301C ; 
 unsigned short SupportHiVision ; 
 unsigned short SupportLCD ; 
 unsigned short SupportRAMDAC2 ; 
 unsigned short SupportTV ; 
 unsigned short SupportTV1024 ; 
 int TVSetPAL ; 
 int TVSimuMode ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 TYPE_2__* XGI330_EModeIDTable ; 
 TYPE_1__* XGI330_RefIndex ; 
 int XGI_SetCRT2ToLCDA ; 

__attribute__((used)) static unsigned char XGI_AjustCRT2Rate(unsigned short ModeIdIndex,
				       unsigned short RefreshRateTableIndex,
				       unsigned short *i,
		struct vb_device_info *pVBInfo)
{
	unsigned short tempax, tempbx, resinfo, modeflag, infoflag;

	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
	resinfo = XGI330_EModeIDTable[ModeIdIndex].Ext_RESINFO;
	tempbx = XGI330_RefIndex[RefreshRateTableIndex + (*i)].ModeID;
	tempax = 0;

	if (pVBInfo->VBInfo & SetCRT2ToRAMDAC) {
		tempax |= SupportRAMDAC2;

		if (pVBInfo->VBType & VB_XGI301C)
			tempax |= SupportCRT2in301C;
	}

	/* 301b */
	if (pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA)) {
		tempax |= SupportLCD;

		if (pVBInfo->LCDResInfo != Panel_1280x1024 &&
		    pVBInfo->LCDResInfo != Panel_1280x960 &&
		    (pVBInfo->LCDInfo & LCDNonExpanding) &&
		    resinfo >= 9)
			return 0;
	}

	if (pVBInfo->VBInfo & SetCRT2ToHiVision) { /* for HiTV */
		tempax |= SupportHiVision;
		if ((pVBInfo->VBInfo & SetInSlaveMode) &&
		    ((resinfo == 4) ||
		     (resinfo == 3 && (pVBInfo->SetFlag & TVSimuMode)) ||
		     (resinfo > 7)))
			return 0;
	} else if (pVBInfo->VBInfo & (SetCRT2ToAVIDEO | SetCRT2ToSVIDEO |
				      SetCRT2ToSCART | SetCRT2ToYPbPr525750 |
				      SetCRT2ToHiVision)) {
		tempax |= SupportTV;

		if (pVBInfo->VBType & (VB_SIS301B | VB_SIS302B | VB_SIS301LV |
				       VB_SIS302LV | VB_XGI301C))
			tempax |= SupportTV1024;

		if (!(pVBInfo->VBInfo & TVSetPAL) &&
		    (modeflag & NoSupportSimuTV) &&
		    (pVBInfo->VBInfo & SetInSlaveMode) &&
		    !(pVBInfo->VBInfo & SetNotSimuMode))
			return 0;
	}

	for (; XGI330_RefIndex[RefreshRateTableIndex + (*i)].ModeID ==
	       tempbx; (*i)--) {
		infoflag = XGI330_RefIndex[RefreshRateTableIndex + (*i)].Ext_InfoFlag;
		if (infoflag & tempax)
			return 1;

		if ((*i) == 0)
			break;
	}

	for ((*i) = 0;; (*i)++) {
		infoflag = XGI330_RefIndex[RefreshRateTableIndex + (*i)].Ext_InfoFlag;
		if (XGI330_RefIndex[RefreshRateTableIndex + (*i)].ModeID
				!= tempbx) {
			return 0;
		}

		if (infoflag & tempax)
			return 1;
	}
	return 1;
}