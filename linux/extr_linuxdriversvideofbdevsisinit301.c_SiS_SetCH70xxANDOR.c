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
struct SiS_Private {int dummy; } ;

/* Variables and functions */
 unsigned short SiS_GetCH70xx (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCH70xx (struct SiS_Private*,unsigned short,unsigned short) ; 

void
SiS_SetCH70xxANDOR(struct SiS_Private *SiS_Pr, unsigned short reg,
		unsigned char myor, unsigned short myand)
{
  unsigned short tempbl;

  tempbl = (SiS_GetCH70xx(SiS_Pr, (reg & 0xFF)) & myand) | myor;
  SiS_SetCH70xx(SiS_Pr, reg, tempbl);
}