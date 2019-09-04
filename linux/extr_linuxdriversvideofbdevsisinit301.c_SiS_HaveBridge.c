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
struct SiS_Private {int SiS_IF_DEF_LVDS; int SiS_VBType; int /*<<< orphan*/  SiS_Part4Port; } ;

/* Variables and functions */
 unsigned short SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int VB_SISVB ; 

__attribute__((used)) static bool
SiS_HaveBridge(struct SiS_Private *SiS_Pr)
{
   unsigned short flag;

   if(SiS_Pr->SiS_IF_DEF_LVDS == 1) {
      return true;
   } else if(SiS_Pr->SiS_VBType & VB_SISVB) {
      flag = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x00);
      if((flag == 1) || (flag == 2)) return true;
   }
   return false;
}