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
 int /*<<< orphan*/  A_REVERSE ; 
 int /*<<< orphan*/  COLOR_PAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_COLOR_HEADER_BAR ; 
 int /*<<< orphan*/  VERSION ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * status_bar_slots ; 
 int /*<<< orphan*/  status_bar_window ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  title_bar_window ; 
 scalar_t__ tui_disabled ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbkgd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void show_title_bar(void)
{
	int i;
	int x = 0;

	if (tui_disabled || !title_bar_window)
		return;

	wattrset(title_bar_window, COLOR_PAIR(PT_COLOR_HEADER_BAR));
	wbkgd(title_bar_window, COLOR_PAIR(PT_COLOR_HEADER_BAR));
	werase(title_bar_window);

	mvwprintw(title_bar_window, 0, 0,
		"     TMON v%s", VERSION);

	wrefresh(title_bar_window);

	werase(status_bar_window);

	for (i = 0; i < 10; i++) {
		if (strlen(status_bar_slots[i]) == 0)
			continue;
		wattron(status_bar_window, A_REVERSE);
		mvwprintw(status_bar_window, 0, x, "%s", status_bar_slots[i]);
		wattroff(status_bar_window, A_REVERSE);
		x += strlen(status_bar_slots[i]) + 1;
	}
	wrefresh(status_bar_window);
}