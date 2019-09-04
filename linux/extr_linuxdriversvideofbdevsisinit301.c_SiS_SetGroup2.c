#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {unsigned short CModeFlag; int SiS_VBInfo; int SiS_TVMode; unsigned char* SiS_PALTiming; int SiS_VBType; unsigned char* SiS_HiTVExtTiming; unsigned char* SiS_HiTVSt2Timing; unsigned char* SiS_HiTVSt1Timing; unsigned char* SiS_NTSCTiming; scalar_t__ SiS_ModeType; unsigned short SiS_RY1COE; unsigned short SiS_RY2COE; unsigned short SiS_RY3COE; unsigned short SiS_RY4COE; unsigned short SiS_VDE; int SiS_VGAHDE; unsigned short SiS_HT; int SiS_VGAVDE; scalar_t__ ChipType; unsigned int SiS_HDE; scalar_t__ SiS_LCDResInfo; int SiS_SetFlag; int SiS_VT; int SiS_LCDInfo; int PanelYRes; unsigned short CVSyncStart; int CVSyncEnd; int PanelXRes; unsigned short CHSyncStart; unsigned short CHSyncEnd; int /*<<< orphan*/  SiS_Part2Port; scalar_t__ UseCustomMode; int /*<<< orphan*/  SiS_Part1Port; int /*<<< orphan*/  SiS_Part4Port; int /*<<< orphan*/  SiS_NewFlickerMode; TYPE_3__* SiS_RefIndex; TYPE_2__* SiS_EModeIDTable; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_6__ {unsigned short Ext_CRT2CRTC; } ;
struct TYPE_5__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_4__ {unsigned short St_ModeFlag; unsigned short St_CRT2CRTC; } ;

/* Variables and functions */
 int DontExpandLCD ; 
 unsigned short HalfDCLK ; 
 int LCDPass11 ; 
 int LCDRGB18Bit ; 
 int LCDVESATiming ; 
 scalar_t__ ModeEGA ; 
 scalar_t__ ModeText ; 
 scalar_t__ ModeVGA ; 
 scalar_t__ Panel_1024x768 ; 
 scalar_t__ Panel_1280x1024 ; 
 scalar_t__ SIS_315H ; 
 int SetCRT2ToAVIDEO ; 
 int SetCRT2ToHiVision ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToSCART ; 
 int SetCRT2ToSVIDEO ; 
 int SetCRT2ToTV ; 
 int SetCRT2ToTVNoHiVision ; 
 int SetCRT2ToTVNoYPbPrHiVision ; 
 int SetCRT2ToYPbPr525750 ; 
 int SetInSlaveMode ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int SiS_GetVGAHT2 (struct SiS_Private*) ; 
 scalar_t__ SiS_IsDualLink (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SetGroup2_Tail (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned char const) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiS_SetTVSpecial (struct SiS_Private*,unsigned short) ; 
 unsigned short* SiS_TVPhase ; 
 unsigned char** SiS_YPbPrTable ; 
 int TVSetNTSC1024 ; 
 int TVSetNTSCJ ; 
 int TVSetPAL ; 
 int TVSetPALM ; 
 int TVSetPALN ; 
 int TVSetTVSimuMode ; 
 int TVSetYPbPr525p ; 
 int TVSetYPbPr750p ; 
 int VB_SIS302LV ; 
 int VB_SIS30xBLV ; 
 int VB_SIS30xCLV ; 
 int VB_SISPART4OVERFLOW ; 

__attribute__((used)) static void
SiS_SetGroup2(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
		unsigned short RefreshRateTableIndex)
{
  unsigned short i, j, tempax, tempbx, tempcx, tempch, tempcl, temp;
  unsigned short push2, modeflag, crt2crtc, bridgeoffset;
  unsigned int   longtemp, PhaseIndex;
  bool           newtvphase;
  const unsigned char *TimingPoint;
#ifdef CONFIG_FB_SIS_315
  unsigned short resindex, CRT2Index;
  const struct SiS_Part2PortTbl *CRT2Part2Ptr = NULL;

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) return;
#endif

  if(ModeNo <= 0x13) {
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     crt2crtc = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
  } else if(SiS_Pr->UseCustomMode) {
     modeflag = SiS_Pr->CModeFlag;
     crt2crtc = 0;
  } else {
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     crt2crtc = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
  }

  temp = 0;
  if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToAVIDEO)) temp |= 0x08;
  if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToSVIDEO)) temp |= 0x04;
  if(SiS_Pr->SiS_VBInfo & SetCRT2ToSCART)     temp |= 0x02;
  if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision)  temp |= 0x01;

  if(!(SiS_Pr->SiS_TVMode & TVSetPAL)) 	      temp |= 0x10;

  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x00,temp);

  PhaseIndex  = 0x01; /* SiS_PALPhase */
  TimingPoint = SiS_Pr->SiS_PALTiming;

  newtvphase = false;
  if( (SiS_Pr->SiS_VBType & VB_SIS30xBLV) &&
      ( (!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) ||
	(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) ) ) {
     newtvphase = true;
  }

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {

     TimingPoint = SiS_Pr->SiS_HiTVExtTiming;
     if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
        TimingPoint = SiS_Pr->SiS_HiTVSt2Timing;
        if(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) {
	   TimingPoint = SiS_Pr->SiS_HiTVSt1Timing;
        }
     }

  } else if(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) {

     i = 0;
     if(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)      i = 2;
     else if(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) i = 1;

     TimingPoint = &SiS_YPbPrTable[i][0];

     PhaseIndex = 0x00; /* SiS_NTSCPhase */

  } else if(SiS_Pr->SiS_TVMode & TVSetPAL) {

     if(newtvphase) PhaseIndex = 0x09; /* SiS_PALPhase2 */

  } else {

     TimingPoint = SiS_Pr->SiS_NTSCTiming;
     PhaseIndex  = (SiS_Pr->SiS_TVMode & TVSetNTSCJ) ? 0x01 : 0x00;	/* SiS_PALPhase : SiS_NTSCPhase */
     if(newtvphase) PhaseIndex += 8;					/* SiS_PALPhase2 : SiS_NTSCPhase2 */

  }

  if(SiS_Pr->SiS_TVMode & (TVSetPALM | TVSetPALN)) {
     PhaseIndex = (SiS_Pr->SiS_TVMode & TVSetPALM) ? 0x02 : 0x03;	/* SiS_PALMPhase : SiS_PALNPhase */
     if(newtvphase) PhaseIndex += 8;					/* SiS_PALMPhase2 : SiS_PALNPhase2 */
  }

  if(SiS_Pr->SiS_TVMode & TVSetNTSC1024) {
     if(SiS_Pr->SiS_TVMode & TVSetPALM) {
        PhaseIndex = 0x05; /* SiS_SpecialPhaseM */
     } else if(SiS_Pr->SiS_TVMode & TVSetNTSCJ) {
        PhaseIndex = 0x11; /* SiS_SpecialPhaseJ */
     } else {
        PhaseIndex = 0x10; /* SiS_SpecialPhase */
     }
  }

  for(i = 0x31, j = 0; i <= 0x34; i++, j++) {
     SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS_TVPhase[(PhaseIndex * 4) + j]);
  }

  for(i = 0x01, j = 0; i <= 0x2D; i++, j++) {
     SiS_SetReg(SiS_Pr->SiS_Part2Port,i,TimingPoint[j]);
  }
  for(i = 0x39; i <= 0x45; i++, j++) {
     SiS_SetReg(SiS_Pr->SiS_Part2Port,i,TimingPoint[j]);
  }

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) {
     if(SiS_Pr->SiS_ModeType != ModeText) {
        SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x3A,0x1F);
     }
  }

  SiS_SetRegOR(SiS_Pr->SiS_Part2Port,0x0A,SiS_Pr->SiS_NewFlickerMode);

  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x35,SiS_Pr->SiS_RY1COE);
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x36,SiS_Pr->SiS_RY2COE);
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x37,SiS_Pr->SiS_RY3COE);
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x38,SiS_Pr->SiS_RY4COE);

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision)	tempax = 950;
  else if(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)  tempax = 680;
  else if(SiS_Pr->SiS_TVMode & TVSetPAL)	tempax = 520;
  else						tempax = 440; /* NTSC, YPbPr 525 */

  if( ((SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) && (SiS_Pr->SiS_VDE <= tempax)) ||
      ( (SiS_Pr->SiS_VBInfo & SetCRT2ToTVNoHiVision) &&
        ((SiS_Pr->SiS_VGAHDE == 1024) || (SiS_Pr->SiS_VDE <= tempax)) ) ) {

     tempax -= SiS_Pr->SiS_VDE;
     tempax >>= 1;
     if(!(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p | TVSetYPbPr750p))) {
        tempax >>= 1;
     }
     tempax &= 0x00ff;

     temp = tempax + (unsigned short)TimingPoint[0];
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,temp);

     temp = tempax + (unsigned short)TimingPoint[1];
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,temp);

     if((SiS_Pr->SiS_VBInfo & SetCRT2ToTVNoYPbPrHiVision) && (SiS_Pr->SiS_VGAHDE >= 1024)) {
        if(SiS_Pr->SiS_TVMode & TVSetPAL) {
           SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,0x1b);
           SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,0x54);
        } else {
           SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,0x17);
           SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,0x1d);
        }
     }

  }

  tempcx = SiS_Pr->SiS_HT;
  if(SiS_IsDualLink(SiS_Pr)) tempcx >>= 1;
  tempcx--;
  if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) tempcx--;
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x1B,tempcx);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1D,0xF0,((tempcx >> 8) & 0x0f));

  tempcx = SiS_Pr->SiS_HT >> 1;
  if(SiS_IsDualLink(SiS_Pr)) tempcx >>= 1;
  tempcx += 7;
  if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) tempcx -= 4;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x22,0x0F,((tempcx << 4) & 0xf0));

  tempbx = TimingPoint[j] | (TimingPoint[j+1] << 8);
  tempbx += tempcx;
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x24,tempbx);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x25,0x0F,((tempbx >> 4) & 0xf0));

  tempbx += 8;
  if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
     tempbx -= 4;
     tempcx = tempbx;
  }
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x29,0x0F,((tempbx << 4) & 0xf0));

  j += 2;
  tempcx += (TimingPoint[j] | (TimingPoint[j+1] << 8));
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x27,tempcx);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x28,0x0F,((tempcx >> 4) & 0xf0));

  tempcx += 8;
  if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) tempcx -= 4;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x2A,0x0F,((tempcx << 4) & 0xf0));

  tempcx = SiS_Pr->SiS_HT >> 1;
  if(SiS_IsDualLink(SiS_Pr)) tempcx >>= 1;
  j += 2;
  tempcx -= (TimingPoint[j] | ((TimingPoint[j+1]) << 8));
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x2D,0x0F,((tempcx << 4) & 0xf0));

  tempcx -= 11;
  if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) {
     tempcx = SiS_GetVGAHT2(SiS_Pr) - 1;
  }
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x2E,tempcx);

  tempbx = SiS_Pr->SiS_VDE;
  if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {
     if(SiS_Pr->SiS_VGAVDE == 360) tempbx = 746;
     if(SiS_Pr->SiS_VGAVDE == 375) tempbx = 746;
     if(SiS_Pr->SiS_VGAVDE == 405) tempbx = 853;
  } else if( (SiS_Pr->SiS_VBInfo & SetCRT2ToTV) &&
             (!(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p|TVSetYPbPr750p))) ) {
     tempbx >>= 1;
     if(SiS_Pr->ChipType >= SIS_315H) {
        if(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) {
	   if((ModeNo <= 0x13) && (crt2crtc == 1)) tempbx++;
	} else if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
	   if(SiS_Pr->SiS_ModeType <= ModeVGA) {
	      if(crt2crtc == 4) tempbx++;
	   }
	}
     }
     if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
        if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
	   if((ModeNo == 0x2f) || (ModeNo == 0x5d) || (ModeNo == 0x5e)) tempbx++;
	}
	if(!(SiS_Pr->SiS_TVMode & TVSetPAL)) {
	   if(ModeNo == 0x03) tempbx++; /* From 1.10.7w - doesn't make sense */
        }
     }
  }
  tempbx -= 2;
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x2F,tempbx);

  temp = (tempcx >> 8) & 0x0F;
  temp |= ((tempbx >> 2) & 0xC0);
  if(SiS_Pr->SiS_VBInfo & (SetCRT2ToSVIDEO | SetCRT2ToAVIDEO)) {
     temp |= 0x10;
     if(SiS_Pr->SiS_VBInfo & SetCRT2ToAVIDEO) temp |= 0x20;
  }
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x30,temp);

  if(SiS_Pr->SiS_VBType & VB_SISPART4OVERFLOW) {
     SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x10,0xdf,((tempbx & 0x0400) >> 5));
  }

  if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {
     tempbx = SiS_Pr->SiS_VDE;
     if( (SiS_Pr->SiS_VBInfo & SetCRT2ToTV) &&
         (!(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p | TVSetYPbPr750p))) ) {
        tempbx >>= 1;
     }
     tempbx -= 3;
     temp = ((tempbx >> 3) & 0x60) | 0x18;
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x46,temp);
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x47,tempbx);

     if(SiS_Pr->SiS_VBType & VB_SISPART4OVERFLOW) {
	SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x10,0xbf,((tempbx & 0x0400) >> 4));
     }
  }

  tempbx = 0;
  if(!(modeflag & HalfDCLK)) {
     if(SiS_Pr->SiS_VGAHDE >= SiS_Pr->SiS_HDE) {
        tempax = 0;
        tempbx |= 0x20;
     }
  }

  tempch = tempcl = 0x01;
  if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) {
     if(SiS_Pr->SiS_VGAHDE >= 960) {
        if((!(modeflag & HalfDCLK)) || (SiS_Pr->ChipType < SIS_315H)) {
	   tempcl = 0x20;
	   if(SiS_Pr->SiS_VGAHDE >= 1280) {
              tempch = 20;
              tempbx &= ~0x20;
           } else {
	      tempch = 25; /* OK */
	   }
        }
     }
  }

  if(!(tempbx & 0x20)) {
     if(modeflag & HalfDCLK) tempcl <<= 1;
     longtemp = ((SiS_Pr->SiS_VGAHDE * tempch) / tempcl) << 13;
     if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) longtemp <<= 3;
     tempax = longtemp / SiS_Pr->SiS_HDE;
     if(longtemp % SiS_Pr->SiS_HDE) tempax++;
     tempbx |= ((tempax >> 8) & 0x1F);
     tempcx = tempax >> 13;
  }

  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x44,tempax);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x45,0xC0,tempbx);

  if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {

     tempcx &= 0x07;
     if(tempbx & 0x20) tempcx = 0;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x46,0xF8,tempcx);

     if(SiS_Pr->SiS_TVMode & TVSetPAL) {
        tempbx = 0x0382;
        tempcx = 0x007e;
     } else {
        tempbx = 0x0369;
        tempcx = 0x0061;
     }
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x4B,tempbx);
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x4C,tempcx);
     temp = (tempcx & 0x0300) >> 6;
     temp |= ((tempbx >> 8) & 0x03);
     if(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) {
        temp |= 0x10;
	if(SiS_Pr->SiS_TVMode & TVSetYPbPr525p)      temp |= 0x20;
	else if(SiS_Pr->SiS_TVMode & TVSetYPbPr750p) temp |= 0x40;
     }
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x4D,temp);

     temp = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x43);
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x43,(temp - 3));

     SiS_SetTVSpecial(SiS_Pr, ModeNo);

     if(SiS_Pr->SiS_VBType & VB_SIS30xCLV) {
        temp = 0;
        if(SiS_Pr->SiS_TVMode & TVSetPALM) temp = 8;
        SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x4e,0xf7,temp);
     }

  }

  if(SiS_Pr->SiS_TVMode & TVSetPALM) {
     if(!(SiS_Pr->SiS_TVMode & TVSetNTSC1024)) {
        temp = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x01);
        SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,(temp - 1));
     }
     SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x00,0xEF);
  }

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) {
     if(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) {
        SiS_SetReg(SiS_Pr->SiS_Part2Port,0x0B,0x00);
     }
  }

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) return;

  /* From here: Part2 LCD setup */

  tempbx = SiS_Pr->SiS_HDE;
  if(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;
  tempbx--;			         	/* RHACTE = HDE - 1 */
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x2C,tempbx);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x2B,0x0F,((tempbx >> 4) & 0xf0));

  temp = 0x01;
  if(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) {
     if(SiS_Pr->SiS_ModeType == ModeEGA) {
        if(SiS_Pr->SiS_VGAHDE >= 1024) {
           temp = 0x02;
           if(SiS_Pr->SiS_SetFlag & LCDVESATiming) {
              temp = 0x01;
	   }
        }
     }
  }
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x0B,temp);

  tempbx = SiS_Pr->SiS_VDE - 1;
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x03,tempbx);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x0C,0xF8,((tempbx >> 8) & 0x07));

  tempcx = SiS_Pr->SiS_VT - 1;
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x19,tempcx);
  temp = (tempcx >> 3) & 0xE0;
  if(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit) {
     /* Enable dithering; only do this for 32bpp mode */
     if(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x01) {
        temp |= 0x10;
     }
  }
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1A,0x0f,temp);

  SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x09,0xF0);
  SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x0A,0xF0);

  SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x17,0xFB);
  SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x18,0xDF);

#ifdef CONFIG_FB_SIS_315
  if(SiS_GetCRT2Part2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex,
                          			&CRT2Index, &resindex)) {
      switch(CRT2Index) {
        case 206: CRT2Part2Ptr = SiS310_CRT2Part2_Asus1024x768_3;    break;
	default:
        case 200: CRT2Part2Ptr = SiS_Pr->SiS_CRT2Part2_1024x768_1;   break;
      }

      SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x01,0x80,(CRT2Part2Ptr+resindex)->CR[0]);
      SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x02,0x80,(CRT2Part2Ptr+resindex)->CR[1]);
      for(i = 2, j = 0x04; j <= 0x06; i++, j++ ) {
        SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
      }
      for(j = 0x1c; j <= 0x1d; i++, j++ ) {
        SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
      }
      for(j = 0x1f; j <= 0x21; i++, j++ ) {
        SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
      }
      SiS_SetReg(SiS_Pr->SiS_Part2Port,0x23,(CRT2Part2Ptr+resindex)->CR[10]);
      SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x25,0x0f,(CRT2Part2Ptr+resindex)->CR[11]);

      SiS_SetGroup2_Tail(SiS_Pr, ModeNo);

  } else {
#endif

    /* Checked for 1024x768, 1280x1024, 1400x1050, 1600x1200 */
    /*             Clevo dual-link 1024x768 */
    /* 		   Compaq 1280x1024 has HT 1696 sometimes (calculation OK, if given HT is correct)  */
    /*		   Acer: OK, but uses different setting for VESA timing at 640/800/1024 and 640x400 */

    if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
       if((SiS_Pr->SiS_LCDInfo & LCDPass11) || (SiS_Pr->PanelYRes == SiS_Pr->SiS_VDE)) {
          tempbx = SiS_Pr->SiS_VDE - 1;
          tempcx = SiS_Pr->SiS_VT - 1;
       } else {
          tempbx = SiS_Pr->SiS_VDE + ((SiS_Pr->PanelYRes - SiS_Pr->SiS_VDE) / 2);
	  tempcx = SiS_Pr->SiS_VT - ((SiS_Pr->PanelYRes - SiS_Pr->SiS_VDE) / 2);
       }
    } else {
       tempbx = SiS_Pr->PanelYRes;
       tempcx = SiS_Pr->SiS_VT;
       tempax = 1;
       if(SiS_Pr->PanelYRes != SiS_Pr->SiS_VDE) {
          tempax = SiS_Pr->PanelYRes;
	  /* if(SiS_Pr->SiS_VGAVDE == 525) tempax += 0x3c;   */  /* 651+301C */
          if(SiS_Pr->PanelYRes < SiS_Pr->SiS_VDE) {
             tempax = tempcx = 0;
          } else {
             tempax -= SiS_Pr->SiS_VDE;
          }
          tempax >>= 1;
       }
       tempcx -= tempax; /* lcdvdes */
       tempbx -= tempax; /* lcdvdee */
    }

    /* Non-expanding: lcdvdes = tempcx = VT-1; lcdvdee = tempbx = VDE-1 */

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x05,tempcx);	/* lcdvdes  */
    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x06,tempbx);	/* lcdvdee  */

    temp = (tempbx >> 5) & 0x38;
    temp |= ((tempcx >> 8) & 0x07);
    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,temp);

    tempax = SiS_Pr->SiS_VDE;
    if((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) {
       tempax = SiS_Pr->PanelYRes;
    }
    tempcx = (SiS_Pr->SiS_VT - tempax) >> 4;
    if((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) {
       if(SiS_Pr->PanelYRes != SiS_Pr->SiS_VDE) {
	  tempcx = (SiS_Pr->SiS_VT - tempax) / 10;
       }
    }

    tempbx = ((SiS_Pr->SiS_VT + SiS_Pr->SiS_VDE) >> 1) - 1;
    if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
       if(SiS_Pr->PanelYRes != SiS_Pr->SiS_VDE) {
          if(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) { /* ? */
             tempax = SiS_Pr->SiS_VT - SiS_Pr->PanelYRes;
	     if(tempax % 4) { tempax >>= 2; tempax++; }
	     else           { tempax >>= 2;           }
             tempbx -= (tempax - 1);
	  } else {
	     tempbx -= 10;
	     if(tempbx <= SiS_Pr->SiS_VDE) tempbx = SiS_Pr->SiS_VDE + 1;
	  }
       }
    }
    if(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) {
       tempbx++;
       if((!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) || (crt2crtc == 6)) {
          if(SiS_Pr->SiS_SetFlag & LCDVESATiming) {
	     tempbx = 770;
	     tempcx = 3;
	  }
       }
    }

    /* non-expanding: lcdvrs = ((VT + VDE) / 2) - 10 */

    if(SiS_Pr->UseCustomMode) {
       tempbx = SiS_Pr->CVSyncStart;
    }

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x04,tempbx);	    /* lcdvrs */

    temp = (tempbx >> 4) & 0xF0;
    tempbx += (tempcx + 1);
    temp |= (tempbx & 0x0F);

    if(SiS_Pr->UseCustomMode) {
       temp &= 0xf0;
       temp |= (SiS_Pr->CVSyncEnd & 0x0f);
    }

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,temp);

#ifdef CONFIG_FB_SIS_300
    SiS_Group2LCDSpecial(SiS_Pr, ModeNo, crt2crtc);
#endif

    bridgeoffset = 7;
    if(SiS_Pr->SiS_VBType & VB_SIS30xBLV)	bridgeoffset += 2;
    if(SiS_Pr->SiS_VBType & VB_SIS30xCLV)	bridgeoffset += 2; /* OK for Averatec 1280x800 (301C) */
    if(SiS_IsDualLink(SiS_Pr))			bridgeoffset++;
    else if(SiS_Pr->SiS_VBType & VB_SIS302LV)	bridgeoffset++;    /* OK for Asus A4L 1280x800 */
    /* Higher bridgeoffset shifts to the LEFT */

    temp = 0;
    if((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) {
       if(SiS_Pr->PanelXRes != SiS_Pr->SiS_HDE) {
	  temp = SiS_Pr->SiS_HT - ((SiS_Pr->PanelXRes - SiS_Pr->SiS_HDE) / 2);
	  if(SiS_IsDualLink(SiS_Pr)) temp >>= 1;
       }
    }
    temp += bridgeoffset;
    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x1F,temp);  	     /* lcdhdes */
    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x20,0x0F,((temp >> 4) & 0xf0));

    tempcx = SiS_Pr->SiS_HT;
    tempax = tempbx = SiS_Pr->SiS_HDE;
    if((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) {
       if(SiS_Pr->PanelXRes != SiS_Pr->SiS_HDE) {
          tempax = SiS_Pr->PanelXRes;
          tempbx = SiS_Pr->PanelXRes - ((SiS_Pr->PanelXRes - SiS_Pr->SiS_HDE) / 2);
       }
    }
    if(SiS_IsDualLink(SiS_Pr)) {
       tempcx >>= 1;
       tempbx >>= 1;
       tempax >>= 1;
    }

    tempbx += bridgeoffset;

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x23,tempbx);	    /* lcdhdee */
    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x25,0xF0,((tempbx >> 8) & 0x0f));

    tempcx = (tempcx - tempax) >> 2;

    tempbx += tempcx;
    push2 = tempbx;

    if(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) {
       if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
          if(SiS_Pr->SiS_LCDInfo & LCDPass11) {
             if(SiS_Pr->SiS_HDE == 1280) tempbx = (tempbx & 0xff00) | 0x47;
	  }
       }
    }

    if(SiS_Pr->UseCustomMode) {
       tempbx = SiS_Pr->CHSyncStart;
       if(modeflag & HalfDCLK) tempbx <<= 1;
       if(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;
       tempbx += bridgeoffset;
    }

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x1C,tempbx);	    /* lcdhrs */
    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1D,0x0F,((tempbx >> 4) & 0xf0));

    tempbx = push2;

    tempcx <<= 1;
    if((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) {
       if(SiS_Pr->PanelXRes != SiS_Pr->SiS_HDE) tempcx >>= 2;
    }
    tempbx += tempcx;

    if(SiS_Pr->UseCustomMode) {
       tempbx = SiS_Pr->CHSyncEnd;
       if(modeflag & HalfDCLK) tempbx <<= 1;
       if(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;
       tempbx += bridgeoffset;
    }

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x21,tempbx);	    /* lcdhre */

    SiS_SetGroup2_Tail(SiS_Pr, ModeNo);

#ifdef CONFIG_FB_SIS_300
    SiS_Set300Part2Regs(SiS_Pr, ModeIdIndex, RefreshRateTableIndex, ModeNo);
#endif
#ifdef CONFIG_FB_SIS_315
  } /* CRT2-LCD from table */
#endif
}