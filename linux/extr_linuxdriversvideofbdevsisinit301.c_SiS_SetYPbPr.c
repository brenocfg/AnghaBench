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
struct SiS_Private {scalar_t__ ChipType; int SiS_VBType; int SiS_VBInfo; void* SiS_YPbPr; int /*<<< orphan*/  SiS_P3d4; } ;

/* Variables and functions */
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_661 ; 
 int SetCRT2ToHiVision ; 
 unsigned char SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int VB_SISYPBPR ; 
 void* YPbPr525i ; 
 void* YPbPr525p ; 
 void* YPbPr750p ; 
 void* YPbPrHiVision ; 

void
SiS_SetYPbPr(struct SiS_Private *SiS_Pr)
{

   unsigned char temp;

   /* Note: This variable is only used on 30xLV systems.
    * CR38 has a different meaning on LVDS/CH7019 systems.
    * On 661 and later, these bits moved to CR35.
    *
    * On 301, 301B, only HiVision 1080i is supported.
    * On 30xLV, 301C, only YPbPr 1080i is supported.
    */

   SiS_Pr->SiS_YPbPr = 0;
   if(SiS_Pr->ChipType >= SIS_661) return;

   if(SiS_Pr->SiS_VBType) {
      if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
	 SiS_Pr->SiS_YPbPr = YPbPrHiVision;
      }
   }

   if(SiS_Pr->ChipType >= SIS_315H) {
      if(SiS_Pr->SiS_VBType & VB_SISYPBPR) {
	 temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
	 if(temp & 0x08) {
	    switch((temp >> 4)) {
	    case 0x00: SiS_Pr->SiS_YPbPr = YPbPr525i;     break;
	    case 0x01: SiS_Pr->SiS_YPbPr = YPbPr525p;     break;
	    case 0x02: SiS_Pr->SiS_YPbPr = YPbPr750p;     break;
	    case 0x03: SiS_Pr->SiS_YPbPr = YPbPrHiVision; break;
	    }
	 }
      }
   }

}