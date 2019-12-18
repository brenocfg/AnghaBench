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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  close_windows () ; 
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  echo () ; 
 int /*<<< orphan*/  endwin () ; 
 scalar_t__ event_tid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_thermal_data () ; 
 int /*<<< orphan*/  input_lock ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nocbreak () ; 
 int /*<<< orphan*/  pthread_cancel (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  set_ctrl_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tmon_log ; 

__attribute__((used)) static void tmon_cleanup(void)
{

	syslog(LOG_INFO, "TMON exit cleanup\n");
	fflush(stdout);
	refresh();
	if (tmon_log)
		fclose(tmon_log);
	if (event_tid) {
		pthread_mutex_lock(&input_lock);
		pthread_cancel(event_tid);
		pthread_mutex_unlock(&input_lock);
		pthread_mutex_destroy(&input_lock);
	}
	closelog();
	/* relax control knobs, undo throttling */
	set_ctrl_state(0);

	keypad(stdscr, FALSE);
	echo();
	nocbreak();
	close_windows();
	endwin();
	free_thermal_data();

	exit(1);
}