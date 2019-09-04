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
struct SiS_Private {int SiS_VBInfo; int SiS_TVMode; unsigned char* SiS_HiTVGroup3Data; unsigned char* SiS_HiTVGroup3Simu; int SiS_VBType; int /*<<< orphan*/  SiS_Part3Port; } ;

/* Variables and functions */
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCDA ; 
 int SetCRT2ToYPbPr525750 ; 
 unsigned char* SiS_HiTVGroup3_1 ; 
 unsigned char* SiS_HiTVGroup3_2 ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned char const) ; 
 int TVSetPAL ; 
 int TVSetPALM ; 
 int TVSetTVSimuMode ; 
 int TVSetYPbPr525i ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int VB_SIS30xCLV ; 

__attribute__((used)) static void
SiS_SetGroup3(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex)
{
  unsigned short i;
  const unsigned char *tempdi;

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) return;

#ifndef SIS_CP
  SiS_SetReg(SiS_Pr->SiS_Part3Port,0x00,0x00);
#else
  SIS_CP_INIT301_CP
#endif

  if(SiS_Pr->SiS_TVMode & TVSetPAL) {
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x13,0xFA);
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x14,0xC8);
  } else {
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x13,0xF5);
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x14,0xB7);
  }

  if(SiS_Pr->SiS_TVMode & TVSetPALM) {
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x13,0xFA);
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x14,0xC8);
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x3D,0xA8);
  }

  tempdi = NULL;
  if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
     tempdi = SiS_Pr->SiS_HiTVGroup3Data;
     if(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) {
        tempdi = SiS_Pr->SiS_HiTVGroup3Simu;
     }
  } else if(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) {
     if(!(SiS_Pr->SiS_TVMode & TVSetYPbPr525i)) {
        tempdi = SiS_HiTVGroup3_1;
        if(SiS_Pr->SiS_TVMode & TVSetYPbPr750p) tempdi = SiS_HiTVGroup3_2;
     }
  }
  if(tempdi) {
     for(i=0; i<=0x3E; i++) {
        SiS_SetReg(SiS_Pr->SiS_Part3Port,i,tempdi[i]);
     }
     if(SiS_Pr->SiS_VBType & VB_SIS30xCLV) {
	if(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) {
	   SiS_SetReg(SiS_Pr->SiS_Part3Port,0x28,0x3f);
	}
     }
  }

#ifdef SIS_CP
  SIS_CP_INIT301_CP2
#endif
}