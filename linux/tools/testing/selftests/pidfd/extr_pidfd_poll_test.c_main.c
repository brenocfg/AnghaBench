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
struct pollfd {int events; int fd; int revents; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int POLLIN ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGKILL ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  alarm (int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  handle_alarm ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,...) ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*) ; 
 int poll (struct pollfd*,int,int) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int strerror (scalar_t__) ; 
 int sys_pidfd_open (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sys_pidfd_send_signal (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ timeout ; 
 scalar_t__ waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	struct pollfd fds;
	int iter, nevents;
	int nr_iterations = 10000;

	fds.events = POLLIN;

	if (argc > 2)
		ksft_exit_fail_msg("Unexpected command line argument\n");

	if (argc == 2) {
		nr_iterations = atoi(argv[1]);
		if (nr_iterations <= 0)
			ksft_exit_fail_msg("invalid input parameter %s\n",
					argv[1]);
	}

	ksft_print_msg("running pidfd poll test for %d iterations\n",
		nr_iterations);

	for (iter = 0; iter < nr_iterations; iter++) {
		int pidfd;
		int child_pid = fork();

		if (child_pid < 0) {
			if (errno == EAGAIN) {
				iter--;
				continue;
			}
			ksft_exit_fail_msg(
				"%s - failed to fork a child process\n",
				strerror(errno));
		}

		if (child_pid == 0) {
			/* Child process just sleeps for a min and exits */
			sleep(60);
			exit(EXIT_SUCCESS);
		}

		/* Parent kills the child and waits for its death */
		pidfd = sys_pidfd_open(child_pid, 0);
		if (pidfd < 0)
			ksft_exit_fail_msg("%s - pidfd_open failed\n",
					strerror(errno));

		/* Setup 3 sec alarm - plenty of time */
		if (signal(SIGALRM, handle_alarm) == SIG_ERR)
			ksft_exit_fail_msg("%s - signal failed\n",
					strerror(errno));
		alarm(3);

		/* Send SIGKILL to the child */
		if (sys_pidfd_send_signal(pidfd, SIGKILL, NULL, 0))
			ksft_exit_fail_msg("%s - pidfd_send_signal failed\n",
					strerror(errno));

		/* Wait for the death notification */
		fds.fd = pidfd;
		nevents = poll(&fds, 1, -1);

		/* Check for error conditions */
		if (nevents < 0)
			ksft_exit_fail_msg("%s - poll failed\n",
					strerror(errno));

		if (nevents != 1)
			ksft_exit_fail_msg("unexpected poll result: %d\n",
					nevents);

		if (!(fds.revents & POLLIN))
			ksft_exit_fail_msg(
				"unexpected event type received: 0x%x\n",
				fds.revents);

		if (timeout)
			ksft_exit_fail_msg(
				"death notification wait timeout\n");

		close(pidfd);
		/* Wait for child to prevent zombies */
		if (waitpid(child_pid, NULL, 0) < 0)
			ksft_exit_fail_msg("%s - waitpid failed\n",
					strerror(errno));

	}

	ksft_test_result_pass("pidfd poll test: pass\n");
	return ksft_exit_pass();
}