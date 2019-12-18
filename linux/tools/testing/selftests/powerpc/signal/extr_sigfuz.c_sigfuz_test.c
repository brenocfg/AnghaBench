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
typedef  int /*<<< orphan*/  ucontext_t ;
struct sigaction {int /*<<< orphan*/  sa_sigaction; void* sa_flags; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int ARG_FOREVER ; 
 int ARG_MESS_WITH_TM_AT ; 
 void* SA_SIGINFO ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int args ; 
 int count_max ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  mess_with_tm () ; 
 scalar_t__ one_in_chance (int) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seg_signal_handler ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srand (scalar_t__) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tmp_uc ; 
 int /*<<< orphan*/  trap_signal_handler ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *sigfuz_test(void *thrid)
{
	struct sigaction trap_sa, seg_sa;
	int ret, i = 0;
	pid_t t;

	tmp_uc = malloc(sizeof(ucontext_t));

	/* Main signal handler */
	trap_sa.sa_flags = SA_SIGINFO;
	trap_sa.sa_sigaction = trap_signal_handler;

	/* SIGSEGV signal handler */
	seg_sa.sa_flags = SA_SIGINFO;
	seg_sa.sa_sigaction = seg_signal_handler;

	/* The signal handler will enable MSR_TS */
	sigaction(SIGUSR1, &trap_sa, NULL);

	/* If it does not crash, it will segfault, avoid it to retest */
	sigaction(SIGSEGV, &seg_sa, NULL);

	while (i < count_max) {
		t = fork();

		if (t == 0) {
			/* Once seed per process */
			srand(time(NULL) + getpid());
			if (args & ARG_MESS_WITH_TM_AT) {
				if (one_in_chance(2))
					mess_with_tm();
			}
			raise(SIGUSR1);
			exit(0);
		} else {
			waitpid(t, &ret, 0);
		}
		if (!(args & ARG_FOREVER))
			i++;
	}

	/* If not freed already, free now */
	if (tmp_uc) {
		free(tmp_uc);
		tmp_uc = NULL;
	}

	return NULL;
}