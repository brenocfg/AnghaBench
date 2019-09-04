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

void
bs_set_clip(int x, int y, int cx, int cy)
{
  g_clip_left1 = x;
  g_clip_top1 = y;
  g_clip_right1 = x + cx;
  g_clip_bottom1 = y + cy;
}