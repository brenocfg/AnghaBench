#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_4__ {int nr_cooling_dev; TYPE_1__* cdi; } ;
struct TYPE_3__ {int /*<<< orphan*/  instance; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_BOLD ; 
 char* DIAG_TITLE ; 
 int /*<<< orphan*/  box (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int diag_dev_rows () ; 
 int /*<<< orphan*/ * dialogue_window ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ *,int,int) ; 
 int maxx ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char*,...) ; 
 TYPE_2__ ptdata ; 
 scalar_t__ tui_disabled ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void show_dialogue(void)
{
	int j, x = 0, y = 0;
	int rows, cols;
	WINDOW *w = dialogue_window;

	if (tui_disabled || !w)
		return;

	getmaxyx(w, rows, cols);

	/* Silence compiler 'unused' warnings */
	(void)cols;

	werase(w);
	box(w, 0, 0);
	mvwprintw(w, 0, maxx/4, DIAG_TITLE);
	/* list all the available tunables */
	for (j = 0; j <= ptdata.nr_cooling_dev; j++) {
		y = j % diag_dev_rows();
		if (y == 0 && j != 0)
			x += 20;
		if (j == ptdata.nr_cooling_dev)
			/* save last choice for target temp */
			mvwprintw(w, y+1, x+1, "%C-%.12s", 'A'+j, "Set Temp");
		else
			mvwprintw(w, y+1, x+1, "%C-%.10s-%2d", 'A'+j,
				ptdata.cdi[j].type, ptdata.cdi[j].instance);
	}
	wattron(w, A_BOLD);
	mvwprintw(w, diag_dev_rows()+1, 1, "Enter Choice [A-Z]?");
	wattroff(w, A_BOLD);
	/* print legend at the bottom line */
	mvwprintw(w, rows - 2, 1,
		"Legend: A=Active, P=Passive, C=Critical");

	wrefresh(dialogue_window);
}