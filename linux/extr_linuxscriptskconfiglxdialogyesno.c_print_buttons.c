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

__attribute__((used)) static void print_buttons(WINDOW * dialog, int height, int width, int selected)
{
	int x = width / 2 - 10;
	int y = height - 2;

	print_button(dialog, " Yes ", y, x, selected == 0);
	print_button(dialog, "  No  ", y, x + 13, selected == 1);

	wmove(dialog, y, x + 1 + 13 * selected);
	wrefresh(dialog);
}