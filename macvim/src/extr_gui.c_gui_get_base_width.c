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
struct TYPE_2__ {int border_offset; scalar_t__ scrollbar_width; scalar_t__* which_scrollbars; } ;

/* Variables and functions */
 size_t SBAR_LEFT ; 
 size_t SBAR_RIGHT ; 
 TYPE_1__ gui ; 

int
gui_get_base_width()
{
    int	    base_width;

    base_width = 2 * gui.border_offset;
    if (gui.which_scrollbars[SBAR_LEFT])
	base_width += gui.scrollbar_width;
    if (gui.which_scrollbars[SBAR_RIGHT])
	base_width += gui.scrollbar_width;
    return base_width;
}