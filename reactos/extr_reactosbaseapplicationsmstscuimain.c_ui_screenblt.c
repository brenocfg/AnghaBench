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
typedef  int uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  bs_screenblt (int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  mi_screen_copy (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ui_invalidate (int,int,int,int) ; 

void
ui_screenblt(uint8 opcode, int x, int y, int cx, int cy,
             int srcx, int srcy)
{
  bs_screenblt(opcode, x, y, cx, cy, srcx, srcy);
  if (opcode == 12)
  {
    mi_screen_copy(x, y, cx, cy, srcx, srcy);
  }
  else
  {
    ui_invalidate(x, y, cx, cy);
  }
}