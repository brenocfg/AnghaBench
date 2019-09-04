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

/* Variables and functions */
 scalar_t__ bs_is_pixel_on (char*,int,int,int,int) ; 
 int /*<<< orphan*/  bs_rect (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  bs_set_pixel (int,int,int,int,int) ; 
 int /*<<< orphan*/  g_hatch_patterns ; 

void
bs_patblt(int opcode, int x, int y, int cx, int cy,
          int brush_style, char * brush_pattern,
          int brush_x_org, int brush_y_org,
          int bgcolour, int fgcolour)
{
  int i;
  int j;
  char ipattern[8];
  char * b;

  b = 0;
  switch (brush_style)
  {
    case 0:
      bs_rect(x, y, cx, cy, fgcolour, opcode);
      break;
    case 2: /* Hatch */
      b = g_hatch_patterns + brush_pattern[0] * 8;
      break;
    case 3:
      for (i = 0; i < 8; i++)
      {
        ipattern[i] = ~brush_pattern[7 - i];
      }
      b = ipattern;
      break;
  }
  if (b != 0)
  {
    for (i = 0; i < cy; i++)
    {
      for (j = 0; j < cx; j++)
      {
        if (bs_is_pixel_on(b, (x + j + brush_x_org) % 8,
                           (y + i + brush_y_org) % 8, 8, 1))
        {
          bs_set_pixel(x + j, y + i, fgcolour, opcode, 1);
        }
        else
        {
          bs_set_pixel(x + j, y + i, bgcolour, opcode, 1);
        }
      }
    }
  }
}