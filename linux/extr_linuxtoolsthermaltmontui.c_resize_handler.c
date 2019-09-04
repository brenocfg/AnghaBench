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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  clear () ; 
 int /*<<< orphan*/  close_windows () ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maxx ; 
 int /*<<< orphan*/  maxy ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  setup_windows () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) (int)) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void resize_handler(int sig)
{
	/* start over when term gets resized, but first we clean up */
	close_windows();
	endwin();
	refresh();
	clear();
	getmaxyx(stdscr, maxy, maxx);  /* get the new screen size */
	setup_windows();
	/* rate limit */
	sleep(1);
	syslog(LOG_DEBUG, "SIG %d, term resized to %d x %d\n",
		sig, maxy, maxx);
	signal(SIGWINCH, resize_handler);
}