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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 size_t MAIN_HEADING ; 
 size_t MAIN_MENU_BOX ; 
 size_t MAIN_MENU_HEADING ; 
 size_t NORMAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * attributes ; 
 int /*<<< orphan*/  box (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  center_item (int,int*) ; 
 int /*<<< orphan*/  clear () ; 
 char const* current_instructions ; 
 int /*<<< orphan*/  curses_menu ; 
 int /*<<< orphan*/  curses_menu_items ; 
 int /*<<< orphan*/ * derwin (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  getmaxx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_window ; 
 int /*<<< orphan*/  menu_backtitle ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char const*) ; 
 int mwin_max_cols ; 
 int mwin_max_lines ; 
 int /*<<< orphan*/  post_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_function_line () ; 
 int /*<<< orphan*/  print_in_middle (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh_all_windows (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scale_menu (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  set_menu_format (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_menu_items (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_menu_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_menu_win (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_menu(const char *prompt, const char *instructions,
		int selected_index, int *last_top_row)
{
	int maxx, maxy;
	WINDOW *menu_window;

	current_instructions = instructions;

	clear();
	(void) wattrset(main_window, attributes[NORMAL]);
	print_in_middle(stdscr, 1, 0, getmaxx(stdscr),
			menu_backtitle,
			attributes[MAIN_HEADING]);

	(void) wattrset(main_window, attributes[MAIN_MENU_BOX]);
	box(main_window, 0, 0);
	(void) wattrset(main_window, attributes[MAIN_MENU_HEADING]);
	mvwprintw(main_window, 0, 3, " %s ", prompt);
	(void) wattrset(main_window, attributes[NORMAL]);

	set_menu_items(curses_menu, curses_menu_items);

	/* position the menu at the middle of the screen */
	scale_menu(curses_menu, &maxy, &maxx);
	maxx = min(maxx, mwin_max_cols-2);
	maxy = mwin_max_lines;
	menu_window = derwin(main_window,
			maxy,
			maxx,
			2,
			(mwin_max_cols-maxx)/2);
	keypad(menu_window, TRUE);
	set_menu_win(curses_menu, menu_window);
	set_menu_sub(curses_menu, menu_window);

	/* must reassert this after changing items, otherwise returns to a
	 * default of 16
	 */
	set_menu_format(curses_menu, maxy, 1);
	center_item(selected_index, last_top_row);
	set_menu_format(curses_menu, maxy, 1);

	print_function_line();

	/* Post the menu */
	post_menu(curses_menu);
	refresh_all_windows(main_window);
}