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
SiS_GetLCDInfoBIOS(struct SiS_Private *SiS_Pr)
{
#ifdef CONFIG_FB_SIS_315
   unsigned char  *ROMAddr;
   unsigned short temp;

   if((ROMAddr = GetLCDStructPtr661(SiS_Pr))) {
      if((temp = SISGETROMW(6)) != SiS_Pr->PanelHT) {
	 SiS_Pr->SiS_NeedRomModeData = true;
	 SiS_Pr->PanelHT  = temp;
      }
      if((temp = SISGETROMW(8)) != SiS_Pr->PanelVT) {
	 SiS_Pr->SiS_NeedRomModeData = true;
	 SiS_Pr->PanelVT  = temp;
      }
      SiS_Pr->PanelHRS = SISGETROMW(10);
      SiS_Pr->PanelHRE = SISGETROMW(12);
      SiS_Pr->PanelVRS = SISGETROMW(14);
      SiS_Pr->PanelVRE = SISGETROMW(16);
      SiS_Pr->PanelVCLKIdx315 = VCLK_CUSTOM_315;
      SiS_Pr->SiS_VCLKData[VCLK_CUSTOM_315].CLOCK =
	 SiS_Pr->SiS_VBVCLKData[VCLK_CUSTOM_315].CLOCK = (unsigned short)((unsigned char)ROMAddr[18]);
      SiS_Pr->SiS_VCLKData[VCLK_CUSTOM_315].SR2B =
	 SiS_Pr->SiS_VBVCLKData[VCLK_CUSTOM_315].Part4_A = ROMAddr[19];
      SiS_Pr->SiS_VCLKData[VCLK_CUSTOM_315].SR2C =
	 SiS_Pr->SiS_VBVCLKData[VCLK_CUSTOM_315].Part4_B = ROMAddr[20];

   }
#endif
}