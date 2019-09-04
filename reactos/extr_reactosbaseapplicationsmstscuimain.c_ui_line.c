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
typedef  int uint8 ;
struct TYPE_3__ {int width; scalar_t__ style; int /*<<< orphan*/  colour; } ;
typedef  TYPE_1__ PEN ;

/* Variables and functions */
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  bs_line (int,int,int,int,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi_line (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_invalidate (int,int,int,int) ; 

void
ui_line(uint8 opcode, int startx, int starty, int endx, int endy,
        PEN * pen)
{
  int x;
  int y;
  int cx;
  int cy;

  bs_line(opcode, startx, starty, endx, endy, pen->width, pen->style,
          pen->colour);
  if (pen->style == 0 && pen->width < 2 && opcode == 12)
  {
    mi_line(startx, starty, endx, endy, pen->colour);
  }
  else
  {
    x = MIN(startx, endx);
    y = MIN(starty, endy);
    cx = (MAX(startx, endx) + 1) - x;
    cy = (MAX(starty, endy) + 1) - y;
    ui_invalidate(x, y, cx, cy);
  }
}