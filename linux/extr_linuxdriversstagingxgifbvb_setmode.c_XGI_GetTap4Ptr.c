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
struct vb_device_info {unsigned short VGAHDE; unsigned short HDE; unsigned short VGAVDE; unsigned short VDE; int TVInfo; int VBInfo; } ;
struct XGI301C_Tap4TimingStruct {int DE; } ;

/* Variables and functions */
 struct XGI301C_Tap4TimingStruct* PALTap4Timing ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToYPbPr525750 ; 
 int TVSetPAL ; 
 int TVSetYPbPr525i ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 struct XGI301C_Tap4TimingStruct* YPbPr750pTap4Timing ; 
 struct XGI301C_Tap4TimingStruct* xgifb_ntsc_525_tap4_timing ; 
 struct XGI301C_Tap4TimingStruct const* xgifb_tap4_timing ; 

__attribute__((used)) static struct XGI301C_Tap4TimingStruct const
*XGI_GetTap4Ptr(unsigned short tempcx, struct vb_device_info *pVBInfo)
{
	unsigned short tempax, tempbx, i;
	struct XGI301C_Tap4TimingStruct const *Tap4TimingPtr;

	if (tempcx == 0) {
		tempax = pVBInfo->VGAHDE;
		tempbx = pVBInfo->HDE;
	} else {
		tempax = pVBInfo->VGAVDE;
		tempbx = pVBInfo->VDE;
	}

	if (tempax <= tempbx)
		return &xgifb_tap4_timing[0];
	Tap4TimingPtr = xgifb_ntsc_525_tap4_timing; /* NTSC */

	if (pVBInfo->TVInfo & TVSetPAL)
		Tap4TimingPtr = PALTap4Timing;

	if (pVBInfo->VBInfo & SetCRT2ToYPbPr525750) {
		if ((pVBInfo->TVInfo & TVSetYPbPr525i) ||
		    (pVBInfo->TVInfo & TVSetYPbPr525p))
			Tap4TimingPtr = xgifb_ntsc_525_tap4_timing;
		if (pVBInfo->TVInfo & TVSetYPbPr750p)
			Tap4TimingPtr = YPbPr750pTap4Timing;
	}

	if (pVBInfo->VBInfo & SetCRT2ToHiVision)
		Tap4TimingPtr = xgifb_tap4_timing;

	i = 0;
	while (Tap4TimingPtr[i].DE != 0xFFFF) {
		if (Tap4TimingPtr[i].DE == tempax)
			break;
		i++;
	}
	return &Tap4TimingPtr[i];
}