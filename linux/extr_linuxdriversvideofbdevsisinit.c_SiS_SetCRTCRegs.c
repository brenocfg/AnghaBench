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
struct SiS_Private {scalar_t__ ChipType; int ChipRevision; int SiS_VBInfo; int /*<<< orphan*/  SiS_P3d4; TYPE_1__* SiS_StandTable; } ;
struct TYPE_2__ {unsigned char* CRTC; } ;

/* Variables and functions */
 scalar_t__ SIS_630 ; 
 scalar_t__ SIS_661 ; 
 scalar_t__ SIS_730 ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToTV ; 
 int SetInSlaveMode ; 
 int /*<<< orphan*/  SiS_OpenCRTC (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
SiS_SetCRTCRegs(struct SiS_Private *SiS_Pr, unsigned short StandTableIndex)
{
   unsigned char  CRTCdata;
   unsigned short i;

   /* Unlock CRTC */
   SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x11,0x7f);

   for(i = 0; i <= 0x18; i++) {
      CRTCdata = SiS_Pr->SiS_StandTable[StandTableIndex].CRTC[i];
      SiS_SetReg(SiS_Pr->SiS_P3d4,i,CRTCdata);
   }

   if(SiS_Pr->ChipType >= SIS_661) {
      SiS_OpenCRTC(SiS_Pr);
      for(i = 0x13; i <= 0x14; i++) {
	 CRTCdata = SiS_Pr->SiS_StandTable[StandTableIndex].CRTC[i];
	 SiS_SetReg(SiS_Pr->SiS_P3d4,i,CRTCdata);
      }
   } else if( ( (SiS_Pr->ChipType == SIS_630) ||
	        (SiS_Pr->ChipType == SIS_730) )  &&
	      (SiS_Pr->ChipRevision >= 0x30) ) {
      if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
	 if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToTV)) {
	    SiS_SetReg(SiS_Pr->SiS_P3d4,0x18,0xFE);
	 }
      }
   }
}