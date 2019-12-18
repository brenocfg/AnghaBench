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
struct pt_regs {scalar_t__ user_syscall_nr; int user_arg0; int user_arg1; int user_arg2; int user_arg3; int user_arg4; int user_arg5; scalar_t__ user_ip; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  PTRACE_GETREGS ; 
 int /*<<< orphan*/  PTRACE_SETREGS ; 
 int /*<<< orphan*/  PTRACE_SYSEMU ; 
 int /*<<< orphan*/  PTRACE_TRACEME ; 
 int /*<<< orphan*/  SIGSTOP ; 
 scalar_t__ SYS_getpid ; 
 scalar_t__ SYS_gettid ; 
 int /*<<< orphan*/  SYS_tgkill ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct pt_regs*) ; 
 scalar_t__ syscall (scalar_t__,...) ; 
 int /*<<< orphan*/  wait_trap (scalar_t__) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_ptrace_syscall_restart(void)
{
	int status;
	struct pt_regs regs;
	pid_t chld;

	printf("[RUN]\tptrace-induced syscall restart\n");

	chld = fork();
	if (chld < 0)
		err(1, "fork");

	/*
	 * Child process is running 4 syscalls after ptrace.
	 *
	 * 1) getpid()
	 * 2) gettid()
	 * 3) tgkill() -> Send SIGSTOP
	 * 4) gettid() -> Where the tests will happen essentially
	 */
	if (chld == 0) {
		if (ptrace(PTRACE_TRACEME, 0, 0, 0) != 0)
			err(1, "PTRACE_TRACEME");

		pid_t pid = getpid(), tid = syscall(SYS_gettid);

		printf("\tChild will make one syscall\n");
		syscall(SYS_tgkill, pid, tid, SIGSTOP);

		syscall(SYS_gettid, 10, 11, 12, 13, 14, 15);
		_exit(0);
	}
	/* Parent process below */

	/* Wait for SIGSTOP sent by tgkill above. */
	if (waitpid(chld, &status, 0) != chld || !WIFSTOPPED(status))
		err(1, "waitpid");

	printf("[RUN]\tSYSEMU\n");
	if (ptrace(PTRACE_SYSEMU, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSEMU");
	wait_trap(chld);

	if (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	/*
	 * Ptrace trapped prior to executing the syscall, thus r3 still has
	 * the syscall number instead of the sys_gettid() result
	 */
	if (regs.user_syscall_nr != SYS_gettid ||
	    regs.user_arg0 != 10 || regs.user_arg1 != 11 ||
	    regs.user_arg2 != 12 || regs.user_arg3 != 13 ||
	    regs.user_arg4 != 14 || regs.user_arg5 != 15) {
		printf("[FAIL]\tInitial args are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n",
			(unsigned long)regs.user_syscall_nr,
			(unsigned long)regs.user_arg0,
			(unsigned long)regs.user_arg1,
			(unsigned long)regs.user_arg2,
			(unsigned long)regs.user_arg3,
			(unsigned long)regs.user_arg4,
			(unsigned long)regs.user_arg5);
		 nerrs++;
	} else {
		printf("[OK]\tInitial nr and args are correct\n"); }

	printf("[RUN]\tRestart the syscall (ip = 0x%lx)\n",
	       (unsigned long)regs.user_ip);

	/*
	 * Rewind to retry the same syscall again. This will basically test
	 * the rewind process together with PTRACE_SETREGS and PTRACE_GETREGS.
	 */
	regs.user_ip -= 4;
	if (ptrace(PTRACE_SETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_SETREGS");

	if (ptrace(PTRACE_SYSEMU, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSEMU");
	wait_trap(chld);

	if (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	if (regs.user_syscall_nr != SYS_gettid ||
	    regs.user_arg0 != 10 || regs.user_arg1 != 11 ||
	    regs.user_arg2 != 12 || regs.user_arg3 != 13 ||
	    regs.user_arg4 != 14 || regs.user_arg5 != 15) {
		printf("[FAIL]\tRestart nr or args are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n",
			(unsigned long)regs.user_syscall_nr,
			(unsigned long)regs.user_arg0,
			(unsigned long)regs.user_arg1,
			(unsigned long)regs.user_arg2,
			(unsigned long)regs.user_arg3,
			(unsigned long)regs.user_arg4,
			(unsigned long)regs.user_arg5);
		nerrs++;
	} else {
		printf("[OK]\tRestarted nr and args are correct\n");
	}

	printf("[RUN]\tChange nr and args and restart the syscall (ip = 0x%lx)\n",
	       (unsigned long)regs.user_ip);

	/*
	 * Inject a new syscall (getpid) in the same place the previous
	 * syscall (gettid), rewind and re-execute.
	 */
	regs.user_syscall_nr = SYS_getpid;
	regs.user_arg0 = 20;
	regs.user_arg1 = 21;
	regs.user_arg2 = 22;
	regs.user_arg3 = 23;
	regs.user_arg4 = 24;
	regs.user_arg5 = 25;
	regs.user_ip -= 4;

	if (ptrace(PTRACE_SETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_SETREGS");

	if (ptrace(PTRACE_SYSEMU, chld, 0, 0) != 0)
		err(1, "PTRACE_SYSEMU");
	wait_trap(chld);

	if (ptrace(PTRACE_GETREGS, chld, 0, &regs) != 0)
		err(1, "PTRACE_GETREGS");

	/* Check that ptrace stopped at the new syscall that was
	 * injected, and guarantee that it haven't executed, i.e, user_args
	 * contain the arguments and not the syscall return value, for
	 * instance.
	 */
	if (regs.user_syscall_nr != SYS_getpid
		|| regs.user_arg0 != 20 || regs.user_arg1 != 21
		|| regs.user_arg2 != 22 || regs.user_arg3 != 23
		|| regs.user_arg4 != 24 || regs.user_arg5 != 25) {

		printf("[FAIL]\tRestart nr or args are wrong (nr=%lu, args=%lu %lu %lu %lu %lu %lu)\n",
			(unsigned long)regs.user_syscall_nr,
			(unsigned long)regs.user_arg0,
			(unsigned long)regs.user_arg1,
			(unsigned long)regs.user_arg2,
			(unsigned long)regs.user_arg3,
			(unsigned long)regs.user_arg4,
			(unsigned long)regs.user_arg5);
		nerrs++;
	} else {
		printf("[OK]\tReplacement nr and args are correct\n");
	}

	if (ptrace(PTRACE_CONT, chld, 0, 0) != 0)
		err(1, "PTRACE_CONT");

	if (waitpid(chld, &status, 0) != chld)
		err(1, "waitpid");

	/* Guarantee that the process executed properly, returning 0 */
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
		printf("[FAIL]\tChild failed\n");
		nerrs++;
	} else {
		printf("[OK]\tChild exited cleanly\n");
	}
}