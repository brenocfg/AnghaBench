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
 int /*<<< orphan*/  bs_copy_memb (char*,char*,int) ; 
 int bs_get_pixel (int,int) ; 
 int /*<<< orphan*/  bs_set_pixel (int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bs_warp_coords (int*,int*,int*,int*,int*,int*) ; 
 int g_Bpp ; 
 char* get_bs_ptr (int,int) ; 

void
bs_screenblt(int rop, int x, int y, int cx, int cy,
             int srcx, int srcy)
{
  int p;
  int i;
  int j;
  char * src;
  char * dst;

  if (bs_warp_coords(&x, &y, &cx, &cy, &srcx, &srcy))
  {
    if (rop == 12) /* copy */
    {
      if (srcy < y) /* copy down - bottom to top */
      {
        for (i = cy - 1; i >= 0; i--)
        {
          src = get_bs_ptr(srcx, srcy + i);
          dst = get_bs_ptr(x, y + i);
          if (src != 0 && dst != 0)
          {
            bs_copy_mem(dst, src, cx * g_Bpp);
          }
        }
      }
      else if (srcy > y || srcx > x) /* copy up or left - top to bottom */
      {
        for (i = 0; i < cy; i++)
        {
          src = get_bs_ptr(srcx, srcy + i);
          dst = get_bs_ptr(x, y + i);
          if (src != 0 && dst != 0)
          {
            bs_copy_mem(dst, src, cx * g_Bpp);
          }
        }
      }
      else /* copy straight right */
      {
        for (i = 0; i < cy; i++)
        {
          src = get_bs_ptr(srcx, srcy + i);
          dst = get_bs_ptr(x, y + i);
          if (src != 0 && dst != 0)
          {
            bs_copy_memb(dst, src, cx * g_Bpp);
          }
        }
      }
    }
    else /* slow */
    {
      if (srcy < y) /* copy down - bottom to top */
      {
        for (i = cy - 1; i >= 0; i--)
        {
          for (j = 0; j < cx; j++)
          {
            p = bs_get_pixel(srcx + j, srcy + i);
            bs_set_pixel(x + j, y + i, p, rop, 0);
          }
        }
      }
      else if (srcy > y || srcx > x) /* copy up or left - top to bottom */
      {
        for (i = 0; i < cy; i++)
        {
          for (j = 0; j < cx; j++)
          {
            p = bs_get_pixel(srcx + j, srcy + i);
            bs_set_pixel(x + j, y + i, p, rop, 0);
          }
        }
      }
      else /* copy straight right */
      {
        for (i = 0; i < cy; i++)
        {
          for (j = cx - 1; j >= 0; j--)
          {
            p = bs_get_pixel(srcx + j, srcy + i);
            bs_set_pixel(x + j, y + i, p, rop, 0);
          }
        }
      }
    }
  }
}