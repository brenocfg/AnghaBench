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

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int MAX_ATTEMPT ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  __builtin_get_texasr () ; 
 int /*<<< orphan*/  __builtin_get_tfiar () ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fail ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,long,long) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  have_htm () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler ; 
 scalar_t__ signaled ; 
 int /*<<< orphan*/  stderr ; 
 int tcheck_transactional () ; 
 long tm_signal_self (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*) ; 

__attribute__((used)) static int test_signal_tm()
{
	int i;
	struct sigaction act;

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

	SKIP_IF(!have_htm());

	for (i = 0; i < MAX_ATTEMPT; i++) {
		/*
		 * If anything bad happens in ASM and we fail to set ret
		 * because *handwave* TM this will cause failure
		 */
		long ret = 0xdead;
		long rc = 0xbeef;

		alarm(0); /* Disable any pending */
		signaled = 0;
		alarm(TIMEOUT);
		FAIL_IF(tcheck_transactional());
		rc = tm_signal_self(getpid(), SIGUSR1, &ret);
		if (ret == 0xdead)
			/*
			 * This basically means the transaction aborted before we
			 * even got to the suspend... this is crazy but it
			 * happens.
			 * Yes this also means we might never make forward
			 * progress... the alarm() will trip eventually...
			 */
			continue;

		if (rc || ret) {
			/* Ret is actually an errno */
			printf("TEXASR 0x%016lx, TFIAR 0x%016lx\n",
					__builtin_get_texasr(), __builtin_get_tfiar());
			fprintf(stderr, "(%d) Fail reason: %d rc=0x%lx ret=0x%lx\n",
					i, fail, rc, ret);
			FAIL_IF(ret);
		}
		while(!signaled && !fail)
			asm volatile("": : :"memory");
		if (!signaled) {
			fprintf(stderr, "(%d) Fail reason: %d rc=0x%lx ret=0x%lx\n",
					i, fail, rc, ret);
			FAIL_IF(fail); /* For the line number */
		}
	}

	return 0;
}