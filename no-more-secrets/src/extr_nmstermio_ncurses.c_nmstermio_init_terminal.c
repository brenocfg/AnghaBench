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
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  cbreak () ; 
 int /*<<< orphan*/  curs_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foregroundColor ; 
 int /*<<< orphan*/  freopen (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ has_colors () ; 
 int /*<<< orphan*/  init_pair (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  start_color () ; 
 int /*<<< orphan*/  stdin ; 

void nmstermio_init_terminal(void) {
	if (!isatty(STDIN_FILENO)) {
		stdin = freopen("/dev/tty", "r", stdin);
	}
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	move(0, 0);
	if (has_colors()) {
		start_color();
		init_pair(1, foregroundColor, COLOR_BLACK);
	}
}