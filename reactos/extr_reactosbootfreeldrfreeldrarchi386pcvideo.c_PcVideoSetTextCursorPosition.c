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
struct TYPE_5__ {int ah; int bh; void* dl; void* dh; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
typedef  TYPE_2__ REGS ;

/* Variables and functions */
 int /*<<< orphan*/  Int386 (int,TYPE_2__*,TYPE_2__*) ; 

VOID
PcVideoSetTextCursorPosition(UCHAR X, UCHAR Y)
{
  REGS Regs;

  /* Int 10h AH=02h
   * VIDEO - SET CURSOR POSITION
   *
   * AH = 02h
   * BH = page number
   * 0-3 in modes 2&3
   * 0-7 in modes 0&1
   * 0 in graphics modes
   * DH = row (00h is top)
   * DL = column (00h is left)
   * Return:
   * Nothing
   */
  Regs.b.ah = 0x02;
  Regs.b.bh = 0x00;
  Regs.b.dh = Y;
  Regs.b.dl = X;
  Int386(0x10, &Regs, &Regs);
}