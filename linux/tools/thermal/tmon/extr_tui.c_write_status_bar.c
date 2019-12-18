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
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  status_bar_window ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void write_status_bar(int x, char *line)
{
	mvwprintw(status_bar_window, 0, x, "%s", line);
	wrefresh(status_bar_window);
}