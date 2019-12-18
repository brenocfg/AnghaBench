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
struct TYPE_5__ {int ah; int bl; int /*<<< orphan*/  al; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
typedef  TYPE_2__ REGS ;

/* Variables and functions */
 int /*<<< orphan*/  Int386 (int,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static VOID
PcVideoSetVerticalResolution(UCHAR VerticalResolutionMode)
{
  REGS Regs;

  /* Int 10h AH=12h BL=30h
   * VIDEO - ALTERNATE FUNCTION SELECT (VGA) - SELECT VERTICAL RESOLUTION
   *
   * AH = 12h
   * BL = 30h
   * AL = vertical resolution
   * 00h 200 scan lines
   * 01h 350 scan lines
   * 02h 400 scan lines
   * Return:
   * AL = 12h if function supported
   *
   * Specify the number of scan lines used to display text modes.
   *
   * The specified resolution will take effect on the next mode set.
   */
  Regs.b.ah = 0x12;
  Regs.b.bl = 0x30;
  Regs.b.al = VerticalResolutionMode;
  Int386(0x10, &Regs, &Regs);
}