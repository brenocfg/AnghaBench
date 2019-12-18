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
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; } ;
typedef  long pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int MAX_ATTEMPT ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int broken ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fps ; 
 long getpid () ; 
 int /*<<< orphan*/  have_htm () ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_usr1 ; 
 long tm_signal_self_context_load (long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tm_signal_context_chk_fpu()
{
	struct sigaction act;
	int i;
	long rc;
	pid_t pid = getpid();

	SKIP_IF(!have_htm());

	act.sa_sigaction = signal_usr1;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) < 0) {
		perror("sigaction sigusr1");
		exit(1);
	}

	i = 0;
	while (i < MAX_ATTEMPT && !broken) {
		/*
		 * tm_signal_self_context_load will set both first and second
		 * contexts accordingly to the values passed through non-NULL
		 * array pointers to it, in that case 'fps', and invoke the
		 * signal handler installed for SIGUSR1.
		 */
		rc = tm_signal_self_context_load(pid, NULL, fps, NULL, NULL);
		FAIL_IF(rc != pid);
		i++;
	}

	return (broken);
}