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
struct SiS_Private {int SiS_VBInfo; int SiS_TVMode; scalar_t__ SiS_ModeType; int SiS_LCDResInfo; int SiS_LCDInfo; scalar_t__ SiS_CHSOverScan; scalar_t__ SiS_IF_DEF_CH70xx; TYPE_3__* SiS_RefIndex; TYPE_2__* SiS_EModeIDTable; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_6__ {unsigned short Ext_CRT2CRTC; } ;
struct TYPE_5__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_4__ {unsigned short St_ModeFlag; unsigned short St_CRT2CRTC; } ;

/* Variables and functions */
 int DontExpandLCD ; 
 unsigned short HalfDCLK ; 
 scalar_t__ ModeVGA ; 
#define  Panel_1024x600 132 
#define  Panel_320x240_1 131 
#define  Panel_320x240_2 130 
#define  Panel_320x240_3 129 
#define  Panel_640x480 128 
 int SetCRT2ToTV ; 
 int TVSetCHOverScan ; 
 int TVSetPAL ; 
 int TVSetPALM ; 

__attribute__((used)) static bool
SiS_GetLVDSCRT1Ptr(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
		   unsigned short RefreshRateTableIndex, unsigned short *ResIndex,
		   unsigned short *DisplayType)
 {
  unsigned short modeflag = 0;
  bool checkhd = true;

  /* Pass 1:1 not supported here */

  if(ModeNo <= 0x13) {
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     (*ResIndex) = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
  } else {
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     (*ResIndex) = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
  }

  (*ResIndex) &= 0x3F;

  if((SiS_Pr->SiS_IF_DEF_CH70xx) && (SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) {

     (*DisplayType) = 80;
     if((SiS_Pr->SiS_TVMode & TVSetPAL) && (!(SiS_Pr->SiS_TVMode & TVSetPALM))) {
      	(*DisplayType) = 82;
	if(SiS_Pr->SiS_ModeType > ModeVGA) {
	   if(SiS_Pr->SiS_CHSOverScan) (*DisplayType) = 84;
	}
     }
     if((*DisplayType) != 84) {
        if(SiS_Pr->SiS_TVMode & TVSetCHOverScan) (*DisplayType)++;
     }

  } else {

     (*DisplayType = 0);
     switch(SiS_Pr->SiS_LCDResInfo) {
     case Panel_320x240_1: (*DisplayType) = 50;
			   checkhd = false;
			   break;
     case Panel_320x240_2: (*DisplayType) = 14;
			   break;
     case Panel_320x240_3: (*DisplayType) = 18;
			   break;
     case Panel_640x480:   (*DisplayType) = 10;
			   break;
     case Panel_1024x600:  (*DisplayType) = 26;
			   break;
     default: return true;
     }

     if(checkhd) {
        if(modeflag & HalfDCLK) (*DisplayType)++;
     }

     if(SiS_Pr->SiS_LCDResInfo == Panel_1024x600) {
        if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) (*DisplayType) += 2;
     }

  }

  return true;
}