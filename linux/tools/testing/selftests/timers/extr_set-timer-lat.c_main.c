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
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;

/* Variables and functions */
 scalar_t__ CLOCK_HWSPECIFIC ; 
 scalar_t__ CLOCK_MONOTONIC_COARSE ; 
 scalar_t__ CLOCK_MONOTONIC_RAW ; 
 scalar_t__ CLOCK_PROCESS_CPUTIME_ID ; 
 scalar_t__ CLOCK_REALTIME_COARSE ; 
 scalar_t__ CLOCK_THREAD_CPUTIME_ID ; 
 scalar_t__ NR_CLOCKIDS ; 
 int SIGRTMAX ; 
 int /*<<< orphan*/  TIMER_ABSTIME ; 
 int TIMER_SECS ; 
 scalar_t__ clock_id ; 
 int do_timer (scalar_t__,int /*<<< orphan*/ ) ; 
 int do_timer_oneshot (scalar_t__,int /*<<< orphan*/ ) ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigalarm ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 

int main(void)
{
	struct sigaction act;
	int signum = SIGRTMAX;
	int ret = 0;

	/* Set up signal handler: */
	sigfillset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = sigalarm;
	sigaction(signum, &act, NULL);

	printf("Setting timers for every %i seconds\n", TIMER_SECS);
	for (clock_id = 0; clock_id < NR_CLOCKIDS; clock_id++) {

		if ((clock_id == CLOCK_PROCESS_CPUTIME_ID) ||
				(clock_id == CLOCK_THREAD_CPUTIME_ID) ||
				(clock_id == CLOCK_MONOTONIC_RAW) ||
				(clock_id == CLOCK_REALTIME_COARSE) ||
				(clock_id == CLOCK_MONOTONIC_COARSE) ||
				(clock_id == CLOCK_HWSPECIFIC))
			continue;

		ret |= do_timer(clock_id, TIMER_ABSTIME);
		ret |= do_timer(clock_id, 0);
		ret |= do_timer_oneshot(clock_id, TIMER_ABSTIME);
		ret |= do_timer_oneshot(clock_id, 0);
	}
	if (ret)
		return ksft_exit_fail();
	return ksft_exit_pass();
}