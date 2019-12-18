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
struct termios {int dummy; } ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct perf_top {int delay_secs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_FS ; 
 int /*<<< orphan*/  EINTR ; 
 int MSEC_PER_SEC ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  PR_SET_NAME ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  __fallthrough ; 
 int /*<<< orphan*/  display_setup_sig () ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  errno ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_top__handle_keypress (struct perf_top*,int) ; 
 int /*<<< orphan*/  perf_top__print_sym_table (struct perf_top*) ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread__unblock_sigwinch () ; 
 int /*<<< orphan*/  set_term_quiet_input (struct termios*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stop_top () ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  unshare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *display_thread(void *arg)
{
	struct pollfd stdin_poll = { .fd = 0, .events = POLLIN };
	struct termios save;
	struct perf_top *top = arg;
	int delay_msecs, c;

	/* In order to read symbols from other namespaces perf to  needs to call
	 * setns(2).  This isn't permitted if the struct_fs has multiple users.
	 * unshare(2) the fs so that we may continue to setns into namespaces
	 * that we're observing.
	 */
	unshare(CLONE_FS);

	prctl(PR_SET_NAME, "perf-top-UI", 0, 0, 0);

	display_setup_sig();
	pthread__unblock_sigwinch();
repeat:
	delay_msecs = top->delay_secs * MSEC_PER_SEC;
	set_term_quiet_input(&save);
	/* trash return*/
	getc(stdin);

	while (!done) {
		perf_top__print_sym_table(top);
		/*
		 * Either timeout expired or we got an EINTR due to SIGWINCH,
		 * refresh screen in both cases.
		 */
		switch (poll(&stdin_poll, 1, delay_msecs)) {
		case 0:
			continue;
		case -1:
			if (errno == EINTR)
				continue;
			__fallthrough;
		default:
			c = getc(stdin);
			tcsetattr(0, TCSAFLUSH, &save);

			if (perf_top__handle_keypress(top, c))
				goto repeat;
			stop_top();
		}
	}

	tcsetattr(0, TCSAFLUSH, &save);
	return NULL;
}