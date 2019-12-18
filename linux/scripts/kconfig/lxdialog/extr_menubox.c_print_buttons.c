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
 int /*<<< orphan*/  print_button (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_buttons(WINDOW * win, int height, int width, int selected)
{
	int x = width / 2 - 28;
	int y = height - 2;

	print_button(win, "Select", y, x, selected == 0);
	print_button(win, " Exit ", y, x + 12, selected == 1);
	print_button(win, " Help ", y, x + 24, selected == 2);
	print_button(win, " Save ", y, x + 36, selected == 3);
	print_button(win, " Load ", y, x + 48, selected == 4);

	wmove(win, y, x + 1 + 12 * selected);
	wrefresh(win);
}