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
 int /*<<< orphan*/  bs_set_pixel (int,int,int,int,int) ; 

void
bs_line(int opcode, int startx, int starty, int endx, int endy,
        int pen_width, int pen_style, int pen_colour)
{
  int dx;
  int dy;
  int incx;
  int incy;
  int dpr;
  int dpru;
  int p;

  if (startx > endx)
  {
    dx = startx - endx;
    incx = -1;
  }
  else
  {
    dx = endx - startx;
    incx = 1;
  }
  if (starty > endy)
  {
    dy = starty - endy;
    incy = -1;
  }
  else
  {
    dy = endy - starty;
    incy = 1;
  }
  if (dx >= dy)
  {
    dpr = dy << 1;
    dpru = dpr - (dx << 1);
    p = dpr - dx;
    for (; dx >= 0; dx--)
    {
      if (startx != endx || starty != endy)
      {
        bs_set_pixel(startx, starty, pen_colour, opcode, 1);
      }
      if (p > 0)
      {
        startx += incx;
        starty += incy;
        p += dpru;
      }
      else
      {
        startx += incx;
        p += dpr;
      }
    }
  }
  else
  {
    dpr = dx << 1;
    dpru = dpr - (dy << 1);
    p = dpr - dy;
    for (; dy >= 0; dy--)
    {
      if (startx != endx || starty != endy)
      {
        bs_set_pixel(startx, starty, pen_colour, opcode, 1);
      }
      if (p > 0)
      {
        startx += incx;
        starty += incy;
        p += dpru;
      }
      else
      {
        starty += incy;
        p += dpr;
      }
    }
  }
}