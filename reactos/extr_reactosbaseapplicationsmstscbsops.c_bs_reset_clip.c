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
 int /*<<< orphan*/  g_clip_bottom1 ; 
 scalar_t__ g_clip_left1 ; 
 int /*<<< orphan*/  g_clip_right1 ; 
 scalar_t__ g_clip_top1 ; 
 int /*<<< orphan*/  g_height1 ; 
 int /*<<< orphan*/  g_width1 ; 

void
bs_reset_clip(void)
{
  g_clip_left1 = 0;
  g_clip_top1 = 0;
  g_clip_right1 = g_width1;
  g_clip_bottom1 = g_height1;
}