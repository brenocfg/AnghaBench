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
 int g_clip_bottom1 ; 
 int g_clip_left1 ; 
 int g_clip_right1 ; 
 int g_clip_top1 ; 

int
bs_warp_coords(int * x, int * y, int * cx, int * cy,
               int * srcx, int * srcy)
{
  int dx;
  int dy;

  if (g_clip_left1 > *x)
  {
    dx = g_clip_left1 - *x;
  }
  else
  {
    dx = 0;
  }
  if (g_clip_top1 > *y)
  {
    dy = g_clip_top1 - *y;
  }
  else
  {
    dy = 0;
  }
  if (*x + *cx > g_clip_right1)
  {
    *cx = (*cx - ((*x + *cx) - g_clip_right1));
  }
  if (*y + *cy > g_clip_bottom1)
  {
    *cy = (*cy - ((*y + *cy) - g_clip_bottom1));
  }
  *cx = *cx - dx;
  *cy = *cy - dy;
  if (*cx <= 0)
  {
    return 0;
  }
  if (*cy <= 0)
  {
    return 0;
  }
  *x = *x + dx;
  *y = *y + dy;
  if (srcx != 0)
  {
    *srcx = *srcx + dx;
  }
  if (srcy != 0)
  {
    *srcy = *srcy + dy;
  }
  return 1;
}