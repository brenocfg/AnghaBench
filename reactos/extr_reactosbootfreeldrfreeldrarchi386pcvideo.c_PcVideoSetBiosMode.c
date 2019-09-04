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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int ah; int /*<<< orphan*/  al; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
typedef  TYPE_2__ REGS ;

/* Variables and functions */
 int /*<<< orphan*/  Int386 (int,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static VOID PcVideoSetBiosMode(UCHAR VideoMode)
{
  REGS Regs;

  /* Int 10h AH=00h
   * VIDEO - SET VIDEO MODE
   *
   * AH = 00h
   * AL = desired video mode
   * Return:
   * AL = video mode flag (Phoenix, AMI BIOS)
   * 20h mode > 7
   * 30h modes 0-5 and 7
   * 3Fh mode 6
   * AL = CRT controller mode byte (Phoenix 386 BIOS v1.10)
   */
  Regs.b.ah = 0x00;
  Regs.b.al = VideoMode;
  Int386(0x10, &Regs, &Regs);
}