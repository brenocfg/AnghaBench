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
SiS_StrangeStuff(struct SiS_Private *SiS_Pr)
{
   /* SiS65x and XGI set up some sort of "lock mode" for text
    * which locks CRT2 in some way to CRT1 timing. Disable
    * this here.
    */
#ifdef CONFIG_FB_SIS_315
   if((IS_SIS651) || (IS_SISM650) ||
      SiS_Pr->ChipType == SIS_340 ||
      SiS_Pr->ChipType == XGI_40) {
      SiS_SetReg(SiS_Pr->SiS_VidCapt, 0x3f, 0x00);   /* Fiddle with capture regs */
      SiS_SetReg(SiS_Pr->SiS_VidCapt, 0x00, 0x00);
      SiS_SetReg(SiS_Pr->SiS_VidPlay, 0x00, 0x86);   /* (BIOS does NOT unlock) */
      SiS_SetRegAND(SiS_Pr->SiS_VidPlay, 0x30, 0xfe); /* Fiddle with video regs */
      SiS_SetRegAND(SiS_Pr->SiS_VidPlay, 0x3f, 0xef);
   }
   /* !!! This does not support modes < 0x13 !!! */
#endif
}