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
 int /*<<< orphan*/  bs_set_clip (int,int,int,int) ; 
 int /*<<< orphan*/  mi_set_clip (int,int,int,int) ; 

void
ui_set_clip(int x, int y, int cx, int cy)
{
  bs_set_clip(x, y, cx, cy);
  mi_set_clip(x, y, cx, cy);
}