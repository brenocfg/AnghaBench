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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * main_window ; 
 int mwin_max_cols ; 
 int mwin_max_lines ; 
 int /*<<< orphan*/  new_panel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newwin (int,int,int,int) ; 
 int /*<<< orphan*/  stdscr ; 

__attribute__((used)) static void setup_windows(void)
{
	int lines, columns;

	getmaxyx(stdscr, lines, columns);

	if (main_window != NULL)
		delwin(main_window);

	/* set up the menu and menu window */
	main_window = newwin(lines-2, columns-2, 2, 1);
	keypad(main_window, TRUE);
	mwin_max_lines = lines-7;
	mwin_max_cols = columns-6;

	/* panels order is from bottom to top */
	new_panel(main_window);
}