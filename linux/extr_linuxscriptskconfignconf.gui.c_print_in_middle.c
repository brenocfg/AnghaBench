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
typedef  int /*<<< orphan*/  chtype ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char*,char const*) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/ * stdscr ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void print_in_middle(WINDOW *win,
		int starty,
		int startx,
		int width,
		const char *string,
		chtype color)
{      int length, x, y;
	float temp;


	if (win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if (startx != 0)
		x = startx;
	if (starty != 0)
		y = starty;
	if (width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length) / 2;
	x = startx + (int)temp;
	(void) wattrset(win, color);
	mvwprintw(win, y, x, "%s", string);
	refresh();
}