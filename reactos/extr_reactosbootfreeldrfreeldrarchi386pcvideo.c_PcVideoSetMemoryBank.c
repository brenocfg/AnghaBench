#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ USHORT ;
struct TYPE_5__ {int ax; int bx; scalar_t__ dx; } ;
struct TYPE_6__ {TYPE_1__ w; } ;
typedef  TYPE_2__ REGS ;

/* Variables and functions */
 scalar_t__ CurrentMemoryBank ; 
 int /*<<< orphan*/  Int386 (int,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static VOID
PcVideoSetMemoryBank(USHORT BankNumber)
{
  REGS Regs;

  if (CurrentMemoryBank != BankNumber)
    {
      /* Int 10h AX=4F05h
       * VESA SuperVGA BIOS - CPU VIDEO MEMORY CONTROL
       *
       * AX = 4F05h
       * BH = subfunction
       * 00h select video memory window
       * 01h get video memory window
       * DX = window address in video memory (in granularity units)
       * Return:
       * DX = window address in video memory (in gran. units)
       * BL = window number
       * 00h window A
       * 01h window B.
       * Return:
       * AL = 4Fh if function supported
       * AH = status
       * 00h successful
       * 01h failed
       */
      Regs.w.ax = 0x4F05;
      Regs.w.bx = 0x0000;
      Regs.w.dx = BankNumber;
      Int386(0x10, &Regs, &Regs);

      if (0x004F == Regs.w.ax)
        {
          CurrentMemoryBank = BankNumber;
    }
    }
}