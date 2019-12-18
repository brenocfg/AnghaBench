#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ si_code; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  PTRACE_GETSIGINFO ; 
 int /*<<< orphan*/  SIGKILL ; 
 scalar_t__ SIGSTOP ; 
 scalar_t__ SIGTRAP ; 
 scalar_t__ TRAP_HWBKPT ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 int /*<<< orphan*/  __WALL ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  child (int,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_print_msg (char*,...) ; 
 int /*<<< orphan*/  ksft_test_result_fail (char*,scalar_t__) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  set_watchpoint (scalar_t__,int,int) ; 
 scalar_t__ strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool arun_test(int wr_size, int wp_size, int wr, int wp)
{
	int status;
	siginfo_t siginfo;
	pid_t pid = fork();
	pid_t wpid;

	if (pid < 0) {
		ksft_test_result_fail(
			"fork() failed: %s\n", strerror(errno));
		return false;
	}
	if (pid == 0)
		child(wr_size, wr);

	wpid = waitpid(pid, &status, __WALL);
	if (wpid != pid) {
		ksft_print_msg(
			"waitpid() failed: %s\n", strerror(errno));
		return false;
	}
	if (!WIFSTOPPED(status)) {
		ksft_print_msg(
			"child did not stop: %s\n", strerror(errno));
		return false;
	}
	if (WSTOPSIG(status) != SIGSTOP) {
		ksft_print_msg("child did not stop with SIGSTOP\n");
		return false;
	}

	if (!set_watchpoint(pid, wp_size, wp))
		return false;

	if (ptrace(PTRACE_CONT, pid, NULL, NULL) < 0) {
		ksft_print_msg(
			"ptrace(PTRACE_SINGLESTEP) failed: %s\n",
			strerror(errno));
		return false;
	}

	alarm(3);
	wpid = waitpid(pid, &status, __WALL);
	if (wpid != pid) {
		ksft_print_msg(
			"waitpid() failed: %s\n", strerror(errno));
		return false;
	}
	alarm(0);
	if (WIFEXITED(status)) {
		ksft_print_msg("child did not single-step\n");
		return false;
	}
	if (!WIFSTOPPED(status)) {
		ksft_print_msg("child did not stop\n");
		return false;
	}
	if (WSTOPSIG(status) != SIGTRAP) {
		ksft_print_msg("child did not stop with SIGTRAP\n");
		return false;
	}
	if (ptrace(PTRACE_GETSIGINFO, pid, NULL, &siginfo) != 0) {
		ksft_print_msg(
			"ptrace(PTRACE_GETSIGINFO): %s\n",
			strerror(errno));
		return false;
	}
	if (siginfo.si_code != TRAP_HWBKPT) {
		ksft_print_msg(
			"Unexpected si_code %d\n", siginfo.si_code);
		return false;
	}

	kill(pid, SIGKILL);
	wpid = waitpid(pid, &status, 0);
	if (wpid != pid) {
		ksft_print_msg(
			"waitpid() failed: %s\n", strerror(errno));
		return false;
	}
	return true;
}