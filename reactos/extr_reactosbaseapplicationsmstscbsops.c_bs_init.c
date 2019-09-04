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
 int /*<<< orphan*/  free (scalar_t__) ; 
 int g_Bpp ; 
 int g_bpp ; 
 scalar_t__ g_bs ; 
 int g_bs_size ; 
 int g_clip_bottom1 ; 
 scalar_t__ g_clip_left1 ; 
 int g_clip_right1 ; 
 scalar_t__ g_clip_top1 ; 
 int g_height1 ; 
 int g_width1 ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

void
bs_init(int width, int height, int bpp)
{
  if (g_bs != 0)
  {
    free(g_bs);
  }
  g_width1 = width;
  g_height1 = height;
  g_bpp = bpp;
  g_Bpp = (bpp + 7) / 8;
  g_bs_size = width * height * g_Bpp;
  g_bs = malloc(g_bs_size);
  memset(g_bs, 0, g_bs_size);
  g_clip_left1 = 0;
  g_clip_top1 = 0;
  g_clip_right1 = width;
  g_clip_bottom1 = height;
}