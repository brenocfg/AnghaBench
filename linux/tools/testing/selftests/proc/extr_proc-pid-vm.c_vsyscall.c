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
struct sigaction {int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_flags; } ;
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGSEGV ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int g_vsyscall ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaction_SIGSEGV ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vsyscall(void)
{
	pid_t pid;
	int wstatus;

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "fork, errno %d\n", errno);
		exit(1);
	}
	if (pid == 0) {
		struct rlimit rlim = {0, 0};
		(void)setrlimit(RLIMIT_CORE, &rlim);

		/* Hide "segfault at ffffffffff600000" messages. */
		struct sigaction act;
		memset(&act, 0, sizeof(struct sigaction));
		act.sa_flags = SA_SIGINFO;
		act.sa_sigaction = sigaction_SIGSEGV;
		(void)sigaction(SIGSEGV, &act, NULL);

		*(volatile int *)0xffffffffff600000UL;
		exit(0);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0) {
		g_vsyscall = true;
	}
}