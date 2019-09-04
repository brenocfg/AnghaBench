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
struct SiS_Private {unsigned short CInfoFlag; scalar_t__ ChipType; int /*<<< orphan*/  SiS_P3c4; int /*<<< orphan*/  SiS_P3d4; TYPE_1__* SiS_RefIndex; scalar_t__ UseCustomMode; } ;
struct TYPE_2__ {unsigned short Ext_InfoFlag; } ;

/* Variables and functions */
 unsigned short InterlaceMode ; 
 unsigned short SiS_GetOffset (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,unsigned short) ; 
 scalar_t__ XGI_20 ; 

__attribute__((used)) static void
SiS_SetCRT1Offset(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex, unsigned short RRTI)
{
   unsigned short temp, DisplayUnit, infoflag;

   if(SiS_Pr->UseCustomMode) {
      infoflag = SiS_Pr->CInfoFlag;
   } else {
      infoflag = SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag;
   }

   DisplayUnit = SiS_GetOffset(SiS_Pr, ModeNo, ModeIdIndex, RRTI);

   temp = (DisplayUnit >> 8) & 0x0f;
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0E,0xF0,temp);

   SiS_SetReg(SiS_Pr->SiS_P3d4,0x13,DisplayUnit & 0xFF);

   if(infoflag & InterlaceMode) DisplayUnit >>= 1;

   DisplayUnit <<= 5;
   temp = (DisplayUnit >> 8) + 1;
   if(DisplayUnit & 0xff) temp++;
   if(SiS_Pr->ChipType == XGI_20) {
      if(ModeNo == 0x4a || ModeNo == 0x49) temp--;
   }
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x10,temp);
}