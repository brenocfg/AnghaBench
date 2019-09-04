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

__attribute__((used)) static void
SiS_CloseCRTC(struct SiS_Private *SiS_Pr)
{
#if 0 /* This locks some CRTC registers. We don't want that. */
   unsigned short temp1 = 0, temp2 = 0;

   if(IS_SIS661741660760) {
      if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) {
         temp1 = 0xa0; temp2 = 0x08;
      }
      SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x51,0x1f,temp1);
      SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x56,0xe7,temp2);
   }
#endif
}