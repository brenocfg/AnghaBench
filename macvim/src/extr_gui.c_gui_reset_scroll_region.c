#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ num_cols; scalar_t__ scroll_region_right; scalar_t__ scroll_region_left; scalar_t__ num_rows; scalar_t__ scroll_region_bot; scalar_t__ scroll_region_top; } ;

/* Variables and functions */
 TYPE_1__ gui ; 

void
gui_reset_scroll_region()
{
    gui.scroll_region_top = 0;
    gui.scroll_region_bot = gui.num_rows - 1;
    gui.scroll_region_left = 0;
    gui.scroll_region_right = gui.num_cols - 1;
}