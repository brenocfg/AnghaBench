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
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_2__ {scalar_t__ rsrc_tooltip_bg_name; void* tooltip_bg_pixel; scalar_t__ rsrc_tooltip_fg_name; void* tooltip_fg_pixel; scalar_t__ rsrc_scroll_bg_name; void* scroll_bg_pixel; scalar_t__ rsrc_scroll_fg_name; void* scroll_fg_pixel; scalar_t__ rsrc_menu_bg_name; void* menu_bg_pixel; scalar_t__ rsrc_menu_fg_name; void* menu_fg_pixel; scalar_t__ in_use; } ;

/* Variables and functions */
 TYPE_1__ gui ; 
 void* gui_get_color (int /*<<< orphan*/ *) ; 

void
gui_mch_def_colors()
{
    /*
     * Get the colors ourselves.  Using the automatic conversion doesn't
     * handle looking for approximate colors.
     */
    if (gui.in_use)
    {
	gui.menu_fg_pixel = gui_get_color((char_u *)gui.rsrc_menu_fg_name);
	gui.menu_bg_pixel = gui_get_color((char_u *)gui.rsrc_menu_bg_name);
	gui.scroll_fg_pixel = gui_get_color((char_u *)gui.rsrc_scroll_fg_name);
	gui.scroll_bg_pixel = gui_get_color((char_u *)gui.rsrc_scroll_bg_name);
#ifdef FEAT_BEVAL
	gui.tooltip_fg_pixel = gui_get_color((char_u *)gui.rsrc_tooltip_fg_name);
	gui.tooltip_bg_pixel = gui_get_color((char_u *)gui.rsrc_tooltip_bg_name);
#endif
    }
}