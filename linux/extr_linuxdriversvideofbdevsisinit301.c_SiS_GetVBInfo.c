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
struct SiS_Private {unsigned short SiS_ModeType; int SiS_VBType; scalar_t__ ChipType; scalar_t__ SiS_IF_DEF_CH70xx; int SiS_IF_DEF_LVDS; unsigned short SiS_VBInfo; int /*<<< orphan*/  SiS_P3d4; TYPE_1__* SiS_EModeIDTable; int /*<<< orphan*/  UseCustomMode; scalar_t__ SiS_SetFlag; } ;
struct TYPE_2__ {unsigned short Ext_RESINFO; } ;

/* Variables and functions */
 unsigned short CRT2Mode ; 
 unsigned short DisableCRT2Display ; 
 unsigned short DriverMode ; 
 unsigned short LoadDACFlag ; 
 unsigned short ModeTypeMask ; 
 unsigned short ModeVGA ; 
 scalar_t__ SIS_315H ; 
 unsigned short SIS_RI_1600x1200 ; 
 unsigned short SetCRT2ToAVIDEO ; 
 unsigned short SetCRT2ToCHYPbPr ; 
 unsigned short SetCRT2ToHiVision ; 
 unsigned short SetCRT2ToLCD ; 
 unsigned short SetCRT2ToLCDA ; 
 unsigned short SetCRT2ToRAMDAC ; 
 unsigned short SetCRT2ToSCART ; 
 unsigned short SetCRT2ToSVIDEO ; 
 unsigned short SetCRT2ToTV ; 
 unsigned short SetCRT2ToYPbPr525750 ; 
 unsigned short SetInSlaveMode ; 
 unsigned short SetNotSimuMode ; 
 unsigned short SetPALTV ; 
 unsigned short SetSimuScanMode ; 
 scalar_t__ SiS_BridgeInSlavemode (struct SiS_Private*) ; 
 scalar_t__ SiS_BridgeIsEnabled (struct SiS_Private*) ; 
 unsigned short SiS_GetModeFlag (struct SiS_Private*,unsigned short,unsigned short) ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SiS_HaveBridge (struct SiS_Private*) ; 
 unsigned short SwitchCRT2 ; 
 int VB_NoLCD ; 
 int VB_SISVB ; 
 int VB_SISVGA2 ; 

void
SiS_GetVBInfo(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex, int checkcrt2mode)
{
   unsigned short tempax, tempbx, temp;
   unsigned short modeflag, resinfo = 0;

   SiS_Pr->SiS_SetFlag = 0;

   modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

   SiS_Pr->SiS_ModeType = modeflag & ModeTypeMask;

   if((ModeNo > 0x13) && (!SiS_Pr->UseCustomMode)) {
      resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
   }

   tempbx = 0;

   if(SiS_HaveBridge(SiS_Pr)) {

	temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
	tempbx |= temp;
	tempax = SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) << 8;
	tempax &= (DriverMode | LoadDACFlag | SetNotSimuMode | SetPALTV);
	tempbx |= tempax;

#ifdef CONFIG_FB_SIS_315
	if(SiS_Pr->ChipType >= SIS_315H) {
	   if(SiS_Pr->SiS_VBType & VB_SISLCDA) {
	      if(ModeNo == 0x03) {
		 /* Mode 0x03 is never in driver mode */
		 SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x31,0xbf);
	      }
	      if(!(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & (DriverMode >> 8))) {
		 /* Reset LCDA setting if not driver mode */
		 SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x38,0xfc);
	      }
	      if(IS_SIS650) {
		 if(SiS_Pr->SiS_UseLCDA) {
		    if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x5f) & 0xF0) {
		       if((ModeNo <= 0x13) || (!(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & (DriverMode >> 8)))) {
			  SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x38,(EnableDualEdge | SetToLCDA));
		       }
		    }
		 }
	      }
	      temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
	      if((temp & (EnableDualEdge | SetToLCDA)) == (EnableDualEdge | SetToLCDA)) {
		 tempbx |= SetCRT2ToLCDA;
	      }
	   }

	   if(SiS_Pr->ChipType >= SIS_661) { /* New CR layout */
	      tempbx &= ~(SetCRT2ToYPbPr525750 | SetCRT2ToHiVision);
	      if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x38) & 0x04) {
		 temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x35) & 0xe0;
		 if(temp == 0x60) tempbx |= SetCRT2ToHiVision;
		 else if(SiS_Pr->SiS_VBType & VB_SISYPBPR) {
		    tempbx |= SetCRT2ToYPbPr525750;
		 }
	      }
	   }

	   if(SiS_Pr->SiS_IF_DEF_LVDS == 1) {
	      temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
	      if(temp & SetToLCDA) {
		 tempbx |= SetCRT2ToLCDA;
	      }
	      if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
		 if(temp & EnableCHYPbPr) {
		    tempbx |= SetCRT2ToCHYPbPr;
		 }
	      }
	   }
	}

#endif  /* CONFIG_FB_SIS_315 */

        if(!(SiS_Pr->SiS_VBType & VB_SISVGA2)) {
	   tempbx &= ~(SetCRT2ToRAMDAC);
	}

	if(SiS_Pr->SiS_VBType & VB_SISVB) {
	   temp = SetCRT2ToSVIDEO   |
		  SetCRT2ToAVIDEO   |
		  SetCRT2ToSCART    |
		  SetCRT2ToLCDA     |
		  SetCRT2ToLCD      |
		  SetCRT2ToRAMDAC   |
		  SetCRT2ToHiVision |
		  SetCRT2ToYPbPr525750;
	} else {
	   if(SiS_Pr->ChipType >= SIS_315H) {
	      if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
		 temp = SetCRT2ToAVIDEO |
		        SetCRT2ToSVIDEO |
		        SetCRT2ToSCART  |
		        SetCRT2ToLCDA   |
		        SetCRT2ToLCD    |
		        SetCRT2ToCHYPbPr;
	      } else {
		 temp = SetCRT2ToLCDA   |
		        SetCRT2ToLCD;
	      }
	   } else {
	      if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
		 temp = SetCRT2ToTV | SetCRT2ToLCD;
	      } else {
		 temp = SetCRT2ToLCD;
	      }
	   }
	}

	if(!(tempbx & temp)) {
	   tempax = DisableCRT2Display;
	   tempbx = 0;
	}

	if(SiS_Pr->SiS_VBType & VB_SISVB) {

	   unsigned short clearmask = ( DriverMode |
				DisableCRT2Display |
				LoadDACFlag 	   |
				SetNotSimuMode 	   |
				SetInSlaveMode 	   |
				SetPALTV 	   |
				SwitchCRT2	   |
				SetSimuScanMode );

	   if(tempbx & SetCRT2ToLCDA)        tempbx &= (clearmask | SetCRT2ToLCDA);
	   if(tempbx & SetCRT2ToRAMDAC)      tempbx &= (clearmask | SetCRT2ToRAMDAC);
	   if(tempbx & SetCRT2ToLCD)         tempbx &= (clearmask | SetCRT2ToLCD);
	   if(tempbx & SetCRT2ToSCART)       tempbx &= (clearmask | SetCRT2ToSCART);
	   if(tempbx & SetCRT2ToHiVision)    tempbx &= (clearmask | SetCRT2ToHiVision);
	   if(tempbx & SetCRT2ToYPbPr525750) tempbx &= (clearmask | SetCRT2ToYPbPr525750);

	} else {

	   if(SiS_Pr->ChipType >= SIS_315H) {
	      if(tempbx & SetCRT2ToLCDA) {
		 tempbx &= (0xFF00|SwitchCRT2|SetSimuScanMode);
	      }
	   }
	   if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
	      if(tempbx & SetCRT2ToTV) {
		 tempbx &= (0xFF00|SetCRT2ToTV|SwitchCRT2|SetSimuScanMode);
	      }
	   }
	   if(tempbx & SetCRT2ToLCD) {
	      tempbx &= (0xFF00|SetCRT2ToLCD|SwitchCRT2|SetSimuScanMode);
	   }
	   if(SiS_Pr->ChipType >= SIS_315H) {
	      if(tempbx & SetCRT2ToLCDA) {
	         tempbx |= SetCRT2ToLCD;
	      }
	   }

	}

	if(tempax & DisableCRT2Display) {
	   if(!(tempbx & (SwitchCRT2 | SetSimuScanMode))) {
	      tempbx = SetSimuScanMode | DisableCRT2Display;
	   }
	}

	if(!(tempbx & DriverMode)) tempbx |= SetSimuScanMode;

	/* LVDS/CHRONTEL (LCD/TV) and 301BDH (LCD) can only be slave in 8bpp modes */
	if(SiS_Pr->SiS_ModeType <= ModeVGA) {
	   if( (SiS_Pr->SiS_IF_DEF_LVDS == 1) ||
	       ((SiS_Pr->SiS_VBType & VB_NoLCD) && (tempbx & SetCRT2ToLCD)) ) {
	      modeflag &= (~CRT2Mode);
	   }
	}

	if(!(tempbx & SetSimuScanMode)) {
	   if(tempbx & SwitchCRT2) {
	      if((!(modeflag & CRT2Mode)) && (checkcrt2mode)) {
		 if(resinfo != SIS_RI_1600x1200) {
		    tempbx |= SetSimuScanMode;
		 }
              }
	   } else {
	      if(SiS_BridgeIsEnabled(SiS_Pr)) {
		 if(!(tempbx & DriverMode)) {
		    if(SiS_BridgeInSlavemode(SiS_Pr)) {
		       tempbx |= SetSimuScanMode;
		    }
		 }
	      }
	   }
	}

	if(!(tempbx & DisableCRT2Display)) {
	   if(tempbx & DriverMode) {
	      if(tempbx & SetSimuScanMode) {
		 if((!(modeflag & CRT2Mode)) && (checkcrt2mode)) {
		    if(resinfo != SIS_RI_1600x1200) {
		       tempbx |= SetInSlaveMode;
		    }
		 }
	      }
	   } else {
	      tempbx |= SetInSlaveMode;
	   }
	}

   }

   SiS_Pr->SiS_VBInfo = tempbx;

#ifdef CONFIG_FB_SIS_300
   if(SiS_Pr->ChipType == SIS_630) {
      SiS_SetChrontelGPIO(SiS_Pr, SiS_Pr->SiS_VBInfo);
   }
#endif

#if 0
   printk(KERN_DEBUG "sisfb: (init301: VBInfo= 0x%04x, SetFlag=0x%04x)\n",
      SiS_Pr->SiS_VBInfo, SiS_Pr->SiS_SetFlag);
#endif
}