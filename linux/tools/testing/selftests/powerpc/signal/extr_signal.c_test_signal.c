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
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int MAX_ATTEMPT ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int TIMEOUT ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fail ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getpid () ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler ; 
 long signal_self (int,int /*<<< orphan*/ ) ; 
 scalar_t__ signaled ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_signal()
{
	int i;
	struct sigaction act;
	pid_t ppid = getpid();
	pid_t pid;

	act.sa_handler = signal_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, NULL) < 0) {
		perror("sigaction SIGUSR1");
		exit(1);
	}
	if (sigaction(SIGALRM, &act, NULL) < 0) {
		perror("sigaction SIGALRM");
		exit(1);
	}

	/* Don't do this for MAX_ATTEMPT, its simply too long */
	for(i  = 0; i < 1000; i++) {
		pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(1);
		}
		if (pid == 0) {
			signal_self(ppid, SIGUSR1);
			exit(1);
		} else {
			alarm(0); /* Disable any pending */
			alarm(2);
			while (!signaled && !fail)
				asm volatile("": : :"memory");
			if (!signaled) {
				fprintf(stderr, "Didn't get signal from child\n");
				FAIL_IF(1); /* For the line number */
			}
			/* Otherwise we'll loop too fast and fork() will eventually fail */
			waitpid(pid, NULL, 0);
		}
	}

	for (i = 0; i < MAX_ATTEMPT; i++) {
		long rc;

		alarm(0); /* Disable any pending */
		signaled = 0;
		alarm(TIMEOUT);
		rc = signal_self(ppid, SIGUSR1);
		if (rc) {
			fprintf(stderr, "(%d) Fail reason: %d rc=0x%lx",
					i, fail, rc);
			FAIL_IF(1); /* For the line number */
		}
		while (!signaled && !fail)
			asm volatile("": : :"memory");
		if (!signaled) {
			fprintf(stderr, "(%d) Fail reason: %d rc=0x%lx",
					i, fail, rc);
			FAIL_IF(1); /* For the line number */
		}
	}

	return 0;
}