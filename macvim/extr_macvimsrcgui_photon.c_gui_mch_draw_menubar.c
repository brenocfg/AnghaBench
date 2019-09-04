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

void
gui_mch_draw_menubar(void)
{
    /* The only time a redraw is needed is when a menu button
     * is added to the menubar, and that is detected and the bar
     * redrawn in gui_mch_add_menu_item
     */
}