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
struct SiS_Private {int SiS_IF_DEF_CH70xx; } ;

/* Variables and functions */
 unsigned short SiS_GetCH700x (struct SiS_Private*,unsigned short) ; 
 unsigned short SiS_GetCH701x (struct SiS_Private*,unsigned short) ; 

__attribute__((used)) static
unsigned short
SiS_GetCH70xx(struct SiS_Private *SiS_Pr, unsigned short tempbx)
{
  if(SiS_Pr->SiS_IF_DEF_CH70xx == 1)
     return SiS_GetCH700x(SiS_Pr, tempbx);
  else
     return SiS_GetCH701x(SiS_Pr, tempbx);
}