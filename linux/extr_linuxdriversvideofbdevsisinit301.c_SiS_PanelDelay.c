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
SiS_PanelDelay(struct SiS_Private *SiS_Pr, unsigned short DelayTime)
{
#if defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
   unsigned char  *ROMAddr = SiS_Pr->VirtualRomBase;
   unsigned short PanelID, DelayIndex, Delay=0;
#endif

   if(SiS_Pr->ChipType < SIS_315H) {

#ifdef CONFIG_FB_SIS_300

      PanelID = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36);
      if(SiS_Pr->SiS_VBType & VB_SISVB) {
	 if(SiS_Pr->SiS_VBType & VB_SIS301) PanelID &= 0xf7;
	 if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x18) & 0x10)) PanelID = 0x12;
      }
      DelayIndex = PanelID >> 4;
      if((DelayTime >= 2) && ((PanelID & 0x0f) == 1))  {
	 Delay = 3;
      } else {
	 if(DelayTime >= 2) DelayTime -= 2;
	 if(!(DelayTime & 0x01)) {
	    Delay = SiS_Pr->SiS_PanelDelayTbl[DelayIndex].timer[0];
	 } else {
	    Delay = SiS_Pr->SiS_PanelDelayTbl[DelayIndex].timer[1];
	 }
	 if(SiS_Pr->SiS_UseROM) {
	    if(ROMAddr[0x220] & 0x40) {
	       if(!(DelayTime & 0x01)) Delay = (unsigned short)ROMAddr[0x225];
	       else 	    	       Delay = (unsigned short)ROMAddr[0x226];
	    }
	 }
      }
      SiS_ShortDelay(SiS_Pr, Delay);

#endif  /* CONFIG_FB_SIS_300 */

   } else {

#ifdef CONFIG_FB_SIS_315

      if((SiS_Pr->ChipType >= SIS_661)    ||
	 (SiS_Pr->ChipType <= SIS_315PRO) ||
	 (SiS_Pr->ChipType == SIS_330)    ||
	 (SiS_Pr->SiS_ROMNew)) {

	 if(!(DelayTime & 0x01)) {
	    SiS_DDC2Delay(SiS_Pr, 0x1000);
	 } else {
	    SiS_DDC2Delay(SiS_Pr, 0x4000);
	 }

      } else if((SiS_Pr->SiS_IF_DEF_LVDS == 1) /* ||
	 (SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) ||
	 (SiS_Pr->SiS_CustomT == CUT_CLEVO1400) */ ) {			/* 315 series, LVDS; Special */

	 if(SiS_Pr->SiS_IF_DEF_CH70xx == 0) {
	    PanelID = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36);
	    if(SiS_Pr->SiS_CustomT == CUT_CLEVO1400) {
	       if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x1b) & 0x10)) PanelID = 0x12;
	    }
	    if(SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) {
	       DelayIndex = PanelID & 0x0f;
	    } else {
	       DelayIndex = PanelID >> 4;
	    }
	    if((DelayTime >= 2) && ((PanelID & 0x0f) == 1))  {
	       Delay = 3;
	    } else {
	       if(DelayTime >= 2) DelayTime -= 2;
	       if(!(DelayTime & 0x01)) {
		  Delay = SiS_Pr->SiS_PanelDelayTblLVDS[DelayIndex].timer[0];
		} else {
		  Delay = SiS_Pr->SiS_PanelDelayTblLVDS[DelayIndex].timer[1];
	       }
	       if((SiS_Pr->SiS_UseROM) && (!(SiS_Pr->SiS_ROMNew))) {
		  if(ROMAddr[0x13c] & 0x40) {
		     if(!(DelayTime & 0x01)) {
			Delay = (unsigned short)ROMAddr[0x17e];
		     } else {
			Delay = (unsigned short)ROMAddr[0x17f];
		     }
		  }
	       }
	    }
	    SiS_ShortDelay(SiS_Pr, Delay);
	 }

      } else if(SiS_Pr->SiS_VBType & VB_SISVB) {			/* 315 series, all bridges */

	 DelayIndex = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) >> 4;
	 if(!(DelayTime & 0x01)) {
	    Delay = SiS_Pr->SiS_PanelDelayTbl[DelayIndex].timer[0];
	 } else {
	    Delay = SiS_Pr->SiS_PanelDelayTbl[DelayIndex].timer[1];
	 }
	 Delay <<= 8;
	 SiS_DDC2Delay(SiS_Pr, Delay);

      }

#endif /* CONFIG_FB_SIS_315 */

   }
}