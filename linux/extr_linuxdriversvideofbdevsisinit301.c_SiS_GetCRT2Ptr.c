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
struct SiS_Private {int SiS_VBType; scalar_t__ SiS_IF_DEF_LVDS; int SiS_VBInfo; unsigned short SiS_LCDResInfo; int SiS_SetFlag; int SiS_LCDInfo; int SiS_TVMode; scalar_t__ SiS_ModeType; scalar_t__ SiS_CHSOverScan; scalar_t__ SiS_IF_DEF_CH70xx; TYPE_3__* SiS_RefIndex; TYPE_2__* SiS_EModeIDTable; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_6__ {unsigned short Ext_CRT2CRTC; unsigned short Ext_CRT2CRTC_NS; } ;
struct TYPE_5__ {unsigned short Ext_RESINFO; } ;
struct TYPE_4__ {unsigned short St_CRT2CRTC; } ;

/* Variables and functions */
 int DontExpandLCD ; 
 int LCDPass11 ; 
 int LCDVESATiming ; 
 scalar_t__ ModeVGA ; 
#define  Panel_1024x600 147 
#define  Panel_1024x768 146 
#define  Panel_1152x768 145 
#define  Panel_1280x1024 144 
#define  Panel_1280x768 143 
 unsigned short Panel_1280x800 ; 
 unsigned short Panel_1280x800_2 ; 
 unsigned short Panel_1280x854 ; 
#define  Panel_1400x1050 142 
#define  Panel_1600x1200 141 
 unsigned short Panel_1680x1050 ; 
#define  Panel_320x240_1 140 
#define  Panel_320x240_2 139 
#define  Panel_320x240_3 138 
#define  Panel_640x480 137 
#define  Panel_800x600 136 
#define  SIS_RI_1024x576 135 
#define  SIS_RI_1024x768 134 
#define  SIS_RI_1280x720 133 
 unsigned short SIS_RI_1280x768 ; 
 unsigned short SIS_RI_1280x800 ; 
 unsigned short SIS_RI_1400x1050 ; 
#define  SIS_RI_512x384 132 
#define  SIS_RI_720x480 131 
#define  SIS_RI_720x576 130 
#define  SIS_RI_768x576 129 
#define  SIS_RI_800x480 128 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToTV ; 
 int SetCRT2ToTVNoHiVision ; 
 int SetCRT2ToYPbPr525750 ; 
 int SetInSlaveMode ; 
 int TVSetCHOverScan ; 
 int TVSetPAL ; 
 int TVSetPALM ; 
 int TVSetPALN ; 
 int TVSetTVSimuMode ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int VB_SISVB ; 

__attribute__((used)) static void
SiS_GetCRT2Ptr(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
	       unsigned short RefreshRateTableIndex, unsigned short *CRT2Index,
	       unsigned short *ResIndex)
{
  unsigned short tempbx=0, tempal=0, resinfo=0;

  if(ModeNo <= 0x13) {
     tempal = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
  } else {
     tempal = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
  }

  if((SiS_Pr->SiS_VBType & VB_SISVB) && (SiS_Pr->SiS_IF_DEF_LVDS == 0)) {

     if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {                            /* LCD */

	tempbx = SiS_Pr->SiS_LCDResInfo;
	if(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) tempbx += 32;

	/* patch index */
	if(SiS_Pr->SiS_LCDResInfo == Panel_1680x1050) {
	   if     (resinfo == SIS_RI_1280x800)  tempal =  9;
	   else if(resinfo == SIS_RI_1400x1050) tempal = 11;
	} else if((SiS_Pr->SiS_LCDResInfo == Panel_1280x800) ||
		  (SiS_Pr->SiS_LCDResInfo == Panel_1280x800_2) ||
		  (SiS_Pr->SiS_LCDResInfo == Panel_1280x854)) {
	   if     (resinfo == SIS_RI_1280x768)  tempal =  9;
	}

	if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
	   /* Pass 1:1 only (center-screen handled outside) */
	   /* This is never called for the panel's native resolution */
	   /* since Pass1:1 will not be set in this case */
	   tempbx = 100;
	   if(ModeNo >= 0x13) {
	      tempal = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC_NS;
	   }
	}

#ifdef CONFIG_FB_SIS_315
	if(SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) {
	   if(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) {
	      if(!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) {
		 tempbx = 200;
		 if(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) tempbx++;
	      }
	   }
	}
#endif

     } else {						  	/* TV */

	if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
	   /* if(SiS_Pr->SiS_VGAVDE > 480) SiS_Pr->SiS_TVMode &= (~TVSetTVSimuMode); */
	   tempbx = 2;
	   if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
	      tempbx = 13;
	      if(!(SiS_Pr->SiS_TVMode & TVSetTVSimuMode)) tempbx = 14;
	   }
	} else if(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) {
	   if(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)	tempbx = 7;
	   else if(SiS_Pr->SiS_TVMode & TVSetYPbPr525p)	tempbx = 6;
	   else						tempbx = 5;
	   if(SiS_Pr->SiS_TVMode & TVSetTVSimuMode)	tempbx += 5;
	} else {
	   if(SiS_Pr->SiS_TVMode & TVSetPAL)		tempbx = 3;
	   else						tempbx = 4;
	   if(SiS_Pr->SiS_TVMode & TVSetTVSimuMode)	tempbx += 5;
	}

     }

     tempal &= 0x3F;

     if(ModeNo > 0x13) {
        if(SiS_Pr->SiS_VBInfo & SetCRT2ToTVNoHiVision) {
	   switch(resinfo) {
	   case SIS_RI_720x480:
	      tempal = 6;
	      if(SiS_Pr->SiS_TVMode & (TVSetPAL | TVSetPALN))	tempal = 9;
	      break;
	   case SIS_RI_720x576:
	   case SIS_RI_768x576:
	   case SIS_RI_1024x576: /* Not in NTSC or YPBPR mode (except 1080i)! */
	      tempal = 6;
	      if(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) {
		 if(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)	tempal = 8;
	      }
	      break;
	   case SIS_RI_800x480:
	      tempal = 4;
	      break;
	   case SIS_RI_512x384:
	   case SIS_RI_1024x768:
	      tempal = 7;
	      if(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) {
		 if(SiS_Pr->SiS_TVMode & TVSetYPbPr525p)	tempal = 8;
	      }
	      break;
	   case SIS_RI_1280x720:
	      if(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) {
		 if(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)	tempal = 9;
	      }
	      break;
	   }
	}
     }

     *CRT2Index = tempbx;
     *ResIndex = tempal;

  } else {   /* LVDS, 301B-DH (if running on LCD) */

     tempbx = 0;
     if((SiS_Pr->SiS_IF_DEF_CH70xx) && (SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) {

	tempbx = 90;
	if(SiS_Pr->SiS_TVMode & TVSetPAL) {
	   tempbx = 92;
	   if(SiS_Pr->SiS_ModeType > ModeVGA) {
	      if(SiS_Pr->SiS_CHSOverScan) tempbx = 99;
	   }
	   if(SiS_Pr->SiS_TVMode & TVSetPALM)      tempbx = 94;
	   else if(SiS_Pr->SiS_TVMode & TVSetPALN) tempbx = 96;
	}
	if(tempbx != 99) {
	   if(SiS_Pr->SiS_TVMode & TVSetCHOverScan) tempbx++;
	}

     } else {

	switch(SiS_Pr->SiS_LCDResInfo) {
	case Panel_640x480:   tempbx = 12; break;
	case Panel_320x240_1: tempbx = 10; break;
	case Panel_320x240_2:
	case Panel_320x240_3: tempbx = 14; break;
	case Panel_800x600:   tempbx = 16; break;
	case Panel_1024x600:  tempbx = 18; break;
	case Panel_1152x768:
	case Panel_1024x768:  tempbx = 20; break;
	case Panel_1280x768:  tempbx = 22; break;
	case Panel_1280x1024: tempbx = 24; break;
	case Panel_1400x1050: tempbx = 26; break;
	case Panel_1600x1200: tempbx = 28; break;
#ifdef CONFIG_FB_SIS_300
	case Panel_Barco1366: tempbx = 80; break;
#endif
	}

	switch(SiS_Pr->SiS_LCDResInfo) {
	case Panel_320x240_1:
	case Panel_320x240_2:
	case Panel_320x240_3:
	case Panel_640x480:
	   break;
	default:
	   if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) tempbx++;
	}

	if(SiS_Pr->SiS_LCDInfo & LCDPass11) tempbx = 30;

#ifdef CONFIG_FB_SIS_300
	if(SiS_Pr->SiS_CustomT == CUT_BARCO1024) {
	   tempbx = 82;
	   if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) tempbx++;
	} else if(SiS_Pr->SiS_CustomT == CUT_PANEL848 || SiS_Pr->SiS_CustomT == CUT_PANEL856) {
	   tempbx = 84;
	   if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) tempbx++;
	}
#endif

     }

     (*CRT2Index) = tempbx;
     (*ResIndex) = tempal & 0x1F;
  }
}