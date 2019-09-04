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
struct SiS_Private {scalar_t__ ChipType; } ;

/* Variables and functions */
 scalar_t__ SIS_315H ; 

__attribute__((used)) static void
SiS_WaitVBRetrace(struct SiS_Private *SiS_Pr)
{
   if(SiS_Pr->ChipType < SIS_315H) {
#ifdef CONFIG_FB_SIS_300
      if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {
	 if(!(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x20)) return;
      }
      if(!(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x80)) {
	 SiS_WaitRetrace1(SiS_Pr);
      } else {
	 SiS_WaitRetrace2(SiS_Pr, 0x25);
      }
#endif
   } else {
#ifdef CONFIG_FB_SIS_315
      if(!(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x40)) {
	 SiS_WaitRetrace1(SiS_Pr);
      } else {
	 SiS_WaitRetrace2(SiS_Pr, 0x30);
      }
#endif
   }
}