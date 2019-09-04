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
struct SiS_Private {int dummy; } ;

/* Variables and functions */

bool
SiS_IsDualEdge(struct SiS_Private *SiS_Pr)
{
#ifdef CONFIG_FB_SIS_315
   if(SiS_Pr->ChipType >= SIS_315H) {
      if((SiS_Pr->ChipType != SIS_650) || (SiS_GetReg(SiS_Pr->SiS_P3d4,0x5f) & 0xf0)) {
	 if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x38) & EnableDualEdge) return true;
      }
   }
#endif
   return false;
}