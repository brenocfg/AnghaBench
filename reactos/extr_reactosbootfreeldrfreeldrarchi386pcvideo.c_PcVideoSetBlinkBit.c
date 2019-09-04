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
struct TYPE_5__ {int ax; int bx; } ;
struct TYPE_6__ {TYPE_1__ w; } ;
typedef  TYPE_2__ REGS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  Int386 (int,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static VOID
PcVideoSetBlinkBit(BOOLEAN Enable)
{
  REGS Regs;

  /* Int 10h AX=1003h
   * VIDEO - TOGGLE INTENSITY/BLINKING BIT (Jr, PS, TANDY 1000, EGA, VGA)
   *
   * AX = 1003h
   * BL = new state
   * 00h background intensity enabled
   * 01h blink enabled
   * BH = 00h to avoid problems on some adapters
   * Return:
   * Nothing
   *
   * Note: although there is no function to get
   * the current status, bit 5 of 0040h:0065h
   * indicates the state.
   */
  Regs.w.ax = 0x1003;
  Regs.w.bx = Enable ? 0x0001 : 0x0000;
  Int386(0x10, &Regs, &Regs);
}