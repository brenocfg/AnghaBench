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
typedef  void* UCHAR ;
struct TYPE_5__ {int ah; int al; void* cl; void* ch; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
typedef  TYPE_2__ REGS ;

/* Variables and functions */
 int /*<<< orphan*/  Int386 (int,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static VOID
PcVideoDefineCursor(UCHAR StartScanLine, UCHAR EndScanLine)
{
  REGS Regs;

  /* Int 10h AH=01h
   * VIDEO - SET TEXT-MODE CURSOR SHAPE
   *
   * AH = 01h
   * CH = cursor start and options
   * CL = bottom scan line containing cursor (bits 0-4)
   * Return:
   * Nothing
   *
   * Specify the starting and ending scan lines to be occupied
   * by the hardware cursor in text modes.
   *
   * AMI 386 BIOS and AST Premier 386 BIOS will lock up the
   * system if AL is not equal to the current video mode.
   *
   * Bitfields for cursor start and options:
   *
   * Bit(s)    Description
   * 7         should be zero
   * 6,5       cursor blink
   * (00=normal, 01=invisible, 10=erratic, 11=slow).
   * (00=normal, other=invisible on EGA/VGA)
   * 4-0       topmost scan line containing cursor
   */
  Regs.b.ah = 0x01;
  Regs.b.al = 0x03;
  Regs.b.ch = StartScanLine;
  Regs.b.cl = EndScanLine;
  Int386(0x10, &Regs, &Regs);
}