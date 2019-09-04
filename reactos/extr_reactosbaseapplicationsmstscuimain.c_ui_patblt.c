#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {int /*<<< orphan*/  yorigin; int /*<<< orphan*/  xorigin; scalar_t__ pattern; int /*<<< orphan*/  style; } ;
typedef  TYPE_1__ BRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  bs_patblt (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ui_invalidate (int,int,int,int) ; 

void
ui_patblt(uint8 opcode, int x, int y, int cx, int cy,
          BRUSH * brush, int bgcolour, int fgcolour)
{
  bs_patblt(opcode, x, y, cx, cy, brush->style, (char *)brush->pattern,
            brush->xorigin, brush->yorigin, bgcolour, fgcolour);
  ui_invalidate(x, y, cx, cy);
}