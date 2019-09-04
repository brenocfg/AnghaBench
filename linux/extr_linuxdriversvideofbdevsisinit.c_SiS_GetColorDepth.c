#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {unsigned short CModeFlag; TYPE_2__* SiS_EModeIDTable; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_4__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_3__ {unsigned short St_ModeFlag; } ;

/* Variables and functions */
 unsigned short ModeEGA ; 
 unsigned short ModeTypeMask ; 

unsigned short
SiS_GetColorDepth(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex)
{
   static const unsigned short ColorDepth[6] = { 1, 2, 4, 4, 6, 8 };
   unsigned short modeflag;
   short index;

   /* Do NOT check UseCustomMode, will skrew up FIFO */
   if(ModeNo == 0xfe) {
      modeflag = SiS_Pr->CModeFlag;
   } else if(ModeNo <= 0x13) {
      modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
   } else {
      modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
   }

   index = (modeflag & ModeTypeMask) - ModeEGA;
   if(index < 0) index = 0;
   return ColorDepth[index];
}