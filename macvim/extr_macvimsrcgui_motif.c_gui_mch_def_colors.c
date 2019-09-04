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
struct TYPE_2__ {int /*<<< orphan*/  scroll_def_bg_pixel; int /*<<< orphan*/  scroll_bg_pixel; int /*<<< orphan*/  scroll_def_fg_pixel; int /*<<< orphan*/  scroll_fg_pixel; int /*<<< orphan*/  menu_def_bg_pixel; int /*<<< orphan*/  menu_bg_pixel; int /*<<< orphan*/  menu_def_fg_pixel; int /*<<< orphan*/  menu_fg_pixel; scalar_t__ in_use; } ;

/* Variables and functions */
 TYPE_1__ gui ; 

void
gui_mch_def_colors()
{
    if (gui.in_use)
    {
	/* Use the values saved when starting up.  These should come from the
	 * window manager or a resources file. */
	gui.menu_fg_pixel = gui.menu_def_fg_pixel;
	gui.menu_bg_pixel = gui.menu_def_bg_pixel;
	gui.scroll_fg_pixel = gui.scroll_def_fg_pixel;
	gui.scroll_bg_pixel = gui.scroll_def_bg_pixel;
#ifdef FEAT_BEVAL
	gui.tooltip_fg_pixel =
			gui_get_color((char_u *)gui.rsrc_tooltip_fg_name);
	gui.tooltip_bg_pixel =
			gui_get_color((char_u *)gui.rsrc_tooltip_bg_name);
#endif
    }
}