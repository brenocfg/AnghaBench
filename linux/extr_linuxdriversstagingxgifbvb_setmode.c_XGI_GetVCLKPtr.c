#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb_device_info {int SetFlag; int LCDInfo; int VBInfo; int VBType; int TVInfo; scalar_t__ P3ca; TYPE_1__* LCDCapList; } ;
struct TYPE_6__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_5__ {unsigned char Ext_CRTVCLK; } ;
struct TYPE_4__ {unsigned char LCD_VCLK; } ;

/* Variables and functions */
 unsigned short Charx8Dot ; 
 int EnableScalingLCD ; 
 unsigned char HiTVSimuVCLK ; 
 unsigned char HiTVTextVCLK ; 
 unsigned char HiTVVCLK ; 
 unsigned char HiTVVCLKDIV2 ; 
 unsigned char NTSC1024VCLK ; 
 int NTSC1024x768 ; 
 int ProgrammingCRT2 ; 
 int RPLLDIV2XO ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToTV ; 
 unsigned char TVCLKBASE_315 ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int TVSimuMode ; 
 unsigned char TVVCLK ; 
 unsigned char TVVCLKDIV2 ; 
 int VB_SIS301B ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302LV ; 
 int VB_XGI301C ; 
 TYPE_3__* XGI330_EModeIDTable ; 
 TYPE_2__* XGI330_RefIndex ; 
 unsigned short XGI_GetLCDCapPtr (struct vb_device_info*) ; 
 int XGI_SetCRT2ToLCDA ; 
 unsigned char XGI_YPbPr750pVCLK ; 
 unsigned char YPbPr525pVCLK ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 

__attribute__((used)) static unsigned char XGI_GetVCLKPtr(unsigned short RefreshRateTableIndex,
				    unsigned short ModeIdIndex,
				    struct vb_device_info *pVBInfo)
{
	unsigned short index, modeflag;
	unsigned char tempal;

	/* si+Ext_ResInfo */
	modeflag = XGI330_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	if ((pVBInfo->SetFlag & ProgrammingCRT2) &&
	    !(pVBInfo->LCDInfo & EnableScalingLCD)) { /* {LCDA/LCDB} */
		index = XGI_GetLCDCapPtr(pVBInfo);
		tempal = pVBInfo->LCDCapList[index].LCD_VCLK;

		if (pVBInfo->VBInfo & (SetCRT2ToLCD | XGI_SetCRT2ToLCDA))
			return tempal;

		/* {TV} */
		if (pVBInfo->VBType &
		    (VB_SIS301B |
		     VB_SIS302B |
		     VB_SIS301LV |
		     VB_SIS302LV |
		     VB_XGI301C)) {
			if (pVBInfo->VBInfo & SetCRT2ToHiVision) {
				tempal = TVCLKBASE_315 + HiTVVCLKDIV2;
				if (!(pVBInfo->TVInfo & RPLLDIV2XO))
					tempal = TVCLKBASE_315 + HiTVVCLK;
				if (pVBInfo->TVInfo & TVSimuMode) {
					tempal = TVCLKBASE_315 + HiTVSimuVCLK;
					if (!(modeflag & Charx8Dot))
						tempal = TVCLKBASE_315 +
								HiTVTextVCLK;
				}
				return tempal;
			}

			if (pVBInfo->TVInfo & TVSetYPbPr750p)
				return XGI_YPbPr750pVCLK;

			if (pVBInfo->TVInfo & TVSetYPbPr525p)
				return YPbPr525pVCLK;

			tempal = NTSC1024VCLK;

			if (!(pVBInfo->TVInfo & NTSC1024x768)) {
				tempal = TVCLKBASE_315 + TVVCLKDIV2;
				if (!(pVBInfo->TVInfo & RPLLDIV2XO))
					tempal = TVCLKBASE_315 + TVVCLK;
			}

			if (pVBInfo->VBInfo & SetCRT2ToTV)
				return tempal;
		}
	} /* {End of VB} */

	inb((pVBInfo->P3ca + 0x02));
	return XGI330_RefIndex[RefreshRateTableIndex].Ext_CRTVCLK;
}