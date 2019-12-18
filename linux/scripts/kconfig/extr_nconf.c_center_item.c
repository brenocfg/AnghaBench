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
 int /*<<< orphan*/  curses_menu ; 
 int /*<<< orphan*/ * curses_menu_items ; 
 int item_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_window ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int mwin_max_lines ; 
 int /*<<< orphan*/  post_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh_all_windows (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_top_row (int /*<<< orphan*/ ,int) ; 
 int top_row (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void center_item(int selected_index, int *last_top_row)
{
	int toprow;

	set_top_row(curses_menu, *last_top_row);
	toprow = top_row(curses_menu);
	if (selected_index < toprow ||
	    selected_index >= toprow+mwin_max_lines) {
		toprow = max(selected_index-mwin_max_lines/2, 0);
		if (toprow >= item_count(curses_menu)-mwin_max_lines)
			toprow = item_count(curses_menu)-mwin_max_lines;
		set_top_row(curses_menu, toprow);
	}
	set_current_item(curses_menu,
			curses_menu_items[selected_index]);
	*last_top_row = toprow;
	post_menu(curses_menu);
	refresh_all_windows(main_window);
}