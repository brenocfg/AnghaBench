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
struct SiS_Private {scalar_t__ ChipType; int /*<<< orphan*/  SiS_Part1Port; } ;

/* Variables and functions */
 scalar_t__ SIS_315H ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ XGI_20 ; 

void
SiS_UnLockCRT2(struct SiS_Private *SiS_Pr)
{
   if(SiS_Pr->ChipType == XGI_20)
      return;
   else if(SiS_Pr->ChipType >= SIS_315H)
      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2f,0x01);
   else
      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x24,0x01);
}