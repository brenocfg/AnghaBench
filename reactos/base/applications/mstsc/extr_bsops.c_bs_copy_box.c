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
 int /*<<< orphan*/  bs_copy_mem (char*,char*,int) ; 
 int g_Bpp ; 
 int g_height1 ; 
 int g_width1 ; 
 char* get_bs_ptr (int,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void
bs_copy_box(char * dst, int x, int y, int cx, int cy, int line_size)
{
  char * src;
  int i;

  /* shouldn't happen */
  if (cx < 1 || cy < 1)
  {
    return;
  }
  /* nothing to draw, memset and leave */
  if (x + cx < 0 || y + cy < 0 || x >= g_width1 || y >= g_height1)
  {
    memset(dst, 0, cx * cy * g_Bpp);
    return;
  }
  /* check if it goes over an edge */
  if (x < 0 || y < 0 || x + cx > g_width1 || y + cy > g_height1)
  {
    memset(dst, 0, cx * cy * g_Bpp);
    if (x < 0)
    {
      cx += x;
      dst += -x * g_Bpp;
      x = 0;
    }
    if (x + cx > g_width1)
    {
      cx = g_width1 - x;
    }
    for (i = 0; i < cy; i++)
    {
      src = get_bs_ptr(x, y + i);
      if (src != 0)
      {
        bs_copy_mem(dst, src, cx * g_Bpp);
      }
      dst += line_size;
    }
  }
  else /* whole box is within */
  {
    for (i = 0; i < cy; i++)
    {
      src = get_bs_ptr(x, y + i);
      if (src != 0)
      {
        bs_copy_mem(dst, src, cx * g_Bpp);
      }
      dst += line_size;
    }
  }
}