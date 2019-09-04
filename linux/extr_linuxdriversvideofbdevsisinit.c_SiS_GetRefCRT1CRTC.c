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
struct SiS_Private {TYPE_1__* SiS_RefIndex; } ;
struct TYPE_2__ {int Ext_InfoFlag; unsigned short Ext_CRT1CRTC_WIDE; unsigned short Ext_CRT1CRTC_NORM; unsigned short Ext_CRT1CRTC; } ;

/* Variables and functions */
 int HaveWideTiming ; 

unsigned short
SiS_GetRefCRT1CRTC(struct SiS_Private *SiS_Pr, unsigned short Index, int UseWide)
{
   if(SiS_Pr->SiS_RefIndex[Index].Ext_InfoFlag & HaveWideTiming) {
      if(UseWide == 1) {
         return SiS_Pr->SiS_RefIndex[Index].Ext_CRT1CRTC_WIDE;
      } else {
         return SiS_Pr->SiS_RefIndex[Index].Ext_CRT1CRTC_NORM;
      }
   } else {
      return SiS_Pr->SiS_RefIndex[Index].Ext_CRT1CRTC;
   }
}