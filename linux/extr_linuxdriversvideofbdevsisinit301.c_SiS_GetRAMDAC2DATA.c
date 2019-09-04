#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {int SiS_RVBHCMAX; int SiS_RVBHCFACT; unsigned short SiS_VGAHT; unsigned short SiS_HT; unsigned short SiS_VGAVT; unsigned short SiS_VT; TYPE_4__* SiS_CRT1Table; int /*<<< orphan*/  SiS_UseWideCRT2; TYPE_3__* SiS_EModeIDTable; TYPE_2__* SiS_StandTable; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_8__ {unsigned short* CR; } ;
struct TYPE_7__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_6__ {unsigned short* CRTC; } ;
struct TYPE_5__ {unsigned short St_ModeFlag; } ;

/* Variables and functions */
 unsigned short Charx8Dot ; 
 unsigned short HalfDCLK ; 
 unsigned short SiS_GetModePtr (struct SiS_Private*,unsigned short,unsigned short) ; 
 unsigned short SiS_GetRefCRT1CRTC (struct SiS_Private*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SiS_GetRAMDAC2DATA(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
		unsigned short RefreshRateTableIndex)
{
  unsigned short tempax=0, tempbx=0, index, dotclock;
  unsigned short temp1=0, modeflag=0, tempcx=0;

  SiS_Pr->SiS_RVBHCMAX  = 1;
  SiS_Pr->SiS_RVBHCFACT = 1;

  if(ModeNo <= 0x13) {

     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     index = SiS_GetModePtr(SiS_Pr,ModeNo,ModeIdIndex);

     tempax = SiS_Pr->SiS_StandTable[index].CRTC[0];
     tempbx = SiS_Pr->SiS_StandTable[index].CRTC[6];
     temp1 = SiS_Pr->SiS_StandTable[index].CRTC[7];

     dotclock = (modeflag & Charx8Dot) ? 8 : 9;

  } else {

     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     index = SiS_GetRefCRT1CRTC(SiS_Pr, RefreshRateTableIndex, SiS_Pr->SiS_UseWideCRT2);

     tempax = SiS_Pr->SiS_CRT1Table[index].CR[0];
     tempax |= (SiS_Pr->SiS_CRT1Table[index].CR[14] << 8);
     tempax &= 0x03FF;
     tempbx = SiS_Pr->SiS_CRT1Table[index].CR[6];
     tempcx = SiS_Pr->SiS_CRT1Table[index].CR[13] << 8;
     tempcx &= 0x0100;
     tempcx <<= 2;
     tempbx |= tempcx;
     temp1  = SiS_Pr->SiS_CRT1Table[index].CR[7];

     dotclock = 8;

  }

  if(temp1 & 0x01) tempbx |= 0x0100;
  if(temp1 & 0x20) tempbx |= 0x0200;

  tempax += 5;
  tempax *= dotclock;
  if(modeflag & HalfDCLK) tempax <<= 1;

  tempbx++;

  SiS_Pr->SiS_VGAHT = SiS_Pr->SiS_HT = tempax;
  SiS_Pr->SiS_VGAVT = SiS_Pr->SiS_VT = tempbx;
}