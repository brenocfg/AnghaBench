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
typedef  int /*<<< orphan*/  SISIOADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetRegByte (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void
SiS_WriteDAC(struct SiS_Private *SiS_Pr, SISIOADDRESS DACData, unsigned short shiftflag,
             unsigned short dl, unsigned short ah, unsigned short al, unsigned short dh)
{
   unsigned short d1, d2, d3;

   switch(dl) {
   case  0: d1 = dh; d2 = ah; d3 = al; break;
   case  1: d1 = ah; d2 = al; d3 = dh; break;
   default: d1 = al; d2 = dh; d3 = ah;
   }
   SiS_SetRegByte(DACData, (d1 << shiftflag));
   SiS_SetRegByte(DACData, (d2 << shiftflag));
   SiS_SetRegByte(DACData, (d3 << shiftflag));
}