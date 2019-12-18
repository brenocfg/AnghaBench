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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_NEWNS ; 
 int /*<<< orphan*/  CLONE_NEWPID ; 
 scalar_t__ ESRCH ; 
 int /*<<< orphan*/  MNT_DETACH ; 
 int MS_PRIVATE ; 
 int MS_REC ; 
 int O_CLOEXEC ; 
 int O_DIRECTORY ; 
 int PIDFD_ERROR ; 
#define  PIDFD_FAIL 131 
 int PIDFD_MAX_DEFAULT ; 
#define  PIDFD_PASS 130 
#define  PIDFD_SKIP 129 
#define  PIDFD_XFAIL 128 
 scalar_t__ PID_RECYCLE ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fork () ; 
 int kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,char const*,...) ; 
 int /*<<< orphan*/  ksft_print_msg (char*,char const*) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*,char const*) ; 
 int mount (char*,char*,char*,int,int /*<<< orphan*/ *) ; 
 int open (char*,int) ; 
 int pipe2 (int*,int) ; 
 int /*<<< orphan*/  read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 int sys_pidfd_send_signal (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umount2 (char*,int /*<<< orphan*/ ) ; 
 int unshare (int /*<<< orphan*/ ) ; 
 int wait_for_pid (scalar_t__) ; 

__attribute__((used)) static int test_pidfd_send_signal_recycled_pid_fail(void)
{
	int i, ret;
	pid_t pid1;
	const char *test_name = "pidfd_send_signal signal recycled pid";

	ret = unshare(CLONE_NEWPID);
	if (ret < 0)
		ksft_exit_fail_msg("%s test: Failed to unshare pid namespace\n",
				   test_name);

	ret = unshare(CLONE_NEWNS);
	if (ret < 0)
		ksft_exit_fail_msg(
			"%s test: Failed to unshare mount namespace\n",
			test_name);

	ret = mount(NULL, "/", NULL, MS_REC | MS_PRIVATE, 0);
	if (ret < 0)
		ksft_exit_fail_msg("%s test: Failed to remount / private\n",
				   test_name);

	/* pid 1 in new pid namespace */
	pid1 = fork();
	if (pid1 < 0)
		ksft_exit_fail_msg("%s test: Failed to create new process\n",
				   test_name);

	if (pid1 == 0) {
		char buf[256];
		pid_t pid2;
		int pidfd = -1;

		(void)umount2("/proc", MNT_DETACH);
		ret = mount("proc", "/proc", "proc", 0, NULL);
		if (ret < 0)
			_exit(PIDFD_ERROR);

		/* grab pid PID_RECYCLE */
		for (i = 0; i <= PIDFD_MAX_DEFAULT; i++) {
			pid2 = fork();
			if (pid2 < 0)
				_exit(PIDFD_ERROR);

			if (pid2 == 0)
				_exit(PIDFD_PASS);

			if (pid2 == PID_RECYCLE) {
				snprintf(buf, sizeof(buf), "/proc/%d", pid2);
				ksft_print_msg("pid to recycle is %d\n", pid2);
				pidfd = open(buf, O_DIRECTORY | O_CLOEXEC);
			}

			if (wait_for_pid(pid2))
				_exit(PIDFD_ERROR);

			if (pid2 >= PID_RECYCLE)
				break;
		}

		/*
		 * We want to be as predictable as we can so if we haven't been
		 * able to grab pid PID_RECYCLE skip the test.
		 */
		if (pid2 != PID_RECYCLE) {
			/* skip test */
			close(pidfd);
			_exit(PIDFD_SKIP);
		}

		if (pidfd < 0)
			_exit(PIDFD_ERROR);

		for (i = 0; i <= PIDFD_MAX_DEFAULT; i++) {
			char c;
			int pipe_fds[2];
			pid_t recycled_pid;
			int child_ret = PIDFD_PASS;

			ret = pipe2(pipe_fds, O_CLOEXEC);
			if (ret < 0)
				_exit(PIDFD_ERROR);

			recycled_pid = fork();
			if (recycled_pid < 0)
				_exit(PIDFD_ERROR);

			if (recycled_pid == 0) {
				close(pipe_fds[1]);
				(void)read(pipe_fds[0], &c, 1);
				close(pipe_fds[0]);

				_exit(PIDFD_PASS);
			}

			/*
			 * Stop the child so we can inspect whether we have
			 * recycled pid PID_RECYCLE.
			 */
			close(pipe_fds[0]);
			ret = kill(recycled_pid, SIGSTOP);
			close(pipe_fds[1]);
			if (ret) {
				(void)wait_for_pid(recycled_pid);
				_exit(PIDFD_ERROR);
			}

			/*
			 * We have recycled the pid. Try to signal it. This
			 * needs to fail since this is a different process than
			 * the one the pidfd refers to.
			 */
			if (recycled_pid == PID_RECYCLE) {
				ret = sys_pidfd_send_signal(pidfd, SIGCONT,
							    NULL, 0);
				if (ret && errno == ESRCH)
					child_ret = PIDFD_XFAIL;
				else
					child_ret = PIDFD_FAIL;
			}

			/* let the process move on */
			ret = kill(recycled_pid, SIGCONT);
			if (ret)
				(void)kill(recycled_pid, SIGKILL);

			if (wait_for_pid(recycled_pid))
				_exit(PIDFD_ERROR);

			switch (child_ret) {
			case PIDFD_FAIL:
				/* fallthrough */
			case PIDFD_XFAIL:
				_exit(child_ret);
			case PIDFD_PASS:
				break;
			default:
				/* not reached */
				_exit(PIDFD_ERROR);
			}

			/*
			 * If the user set a custom pid_max limit we could be
			 * in the millions.
			 * Skip the test in this case.
			 */
			if (recycled_pid > PIDFD_MAX_DEFAULT)
				_exit(PIDFD_SKIP);
		}

		/* failed to recycle pid */
		_exit(PIDFD_SKIP);
	}

	ret = wait_for_pid(pid1);
	switch (ret) {
	case PIDFD_FAIL:
		ksft_exit_fail_msg(
			"%s test: Managed to signal recycled pid %d\n",
			test_name, PID_RECYCLE);
	case PIDFD_PASS:
		ksft_exit_fail_msg("%s test: Failed to recycle pid %d\n",
				   test_name, PID_RECYCLE);
	case PIDFD_SKIP:
		ksft_print_msg("%s test: Skipping test\n", test_name);
		ret = 0;
		break;
	case PIDFD_XFAIL:
		ksft_test_result_pass(
			"%s test: Failed to signal recycled pid as expected\n",
			test_name);
		ret = 0;
		break;
	default /* PIDFD_ERROR */:
		ksft_exit_fail_msg("%s test: Error while running tests\n",
				   test_name);
	}

	return ret;
}