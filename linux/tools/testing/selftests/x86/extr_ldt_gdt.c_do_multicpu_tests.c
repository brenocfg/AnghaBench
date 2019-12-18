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
struct user_desc {int limit; int seg_32bit; int limit_in_pages; int /*<<< orphan*/  useable; int /*<<< orphan*/  seg_not_present; int /*<<< orphan*/  read_exec_only; int /*<<< orphan*/  contents; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  entry_number; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  desc ;
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  FUTEX_WAKE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SYS_futex ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int ftx ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ safe_modify_ldt (int,struct user_desc*,int) ; 
 scalar_t__ sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sethandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsegv ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  threadproc ; 

__attribute__((used)) static void do_multicpu_tests(void)
{
	cpu_set_t cpuset;
	pthread_t thread;
	int failures = 0, iters = 5, i;
	unsigned short orig_ss;

	CPU_ZERO(&cpuset);
	CPU_SET(1, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0) {
		printf("[SKIP]\tCannot set affinity to CPU 1\n");
		return;
	}

	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0) {
		printf("[SKIP]\tCannot set affinity to CPU 0\n");
		return;
	}

	sethandler(SIGSEGV, sigsegv, 0);
#ifdef __i386__
	/* True 32-bit kernels send SIGILL instead of SIGSEGV on IRET faults. */
	sethandler(SIGILL, sigsegv, 0);
#endif

	printf("[RUN]\tCross-CPU LDT invalidation\n");

	if (pthread_create(&thread, 0, threadproc, 0) != 0)
		err(1, "pthread_create");

	asm volatile ("mov %%ss, %0" : "=rm" (orig_ss));

	for (i = 0; i < 5; i++) {
		if (sigsetjmp(jmpbuf, 1) != 0)
			continue;

		/* Make sure the thread is ready after the last test. */
		while (ftx != 0)
			;

		struct user_desc desc = {
			.entry_number    = 0,
			.base_addr       = 0,
			.limit           = 0xfffff,
			.seg_32bit       = 1,
			.contents        = 0, /* Data */
			.read_exec_only  = 0,
			.limit_in_pages  = 1,
			.seg_not_present = 0,
			.useable         = 0
		};

		if (safe_modify_ldt(0x11, &desc, sizeof(desc)) != 0) {
			if (errno != ENOSYS)
				err(1, "modify_ldt");
			printf("[SKIP]\tmodify_ldt unavailable\n");
			break;
		}

		/* Arm the thread. */
		ftx = 1;
		syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, NULL, NULL, 0);

		asm volatile ("mov %0, %%ss" : : "r" (0x7));

		/* Go! */
		ftx = 2;

		while (ftx != 0)
			;

		/*
		 * On success, modify_ldt will segfault us synchronously,
		 * and we'll escape via siglongjmp.
		 */

		failures++;
		asm volatile ("mov %0, %%ss" : : "rm" (orig_ss));
	};

	ftx = 100;  /* Kill the thread. */
	syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, NULL, NULL, 0);

	if (pthread_join(thread, NULL) != 0)
		err(1, "pthread_join");

	if (failures) {
		printf("[FAIL]\t%d of %d iterations failed\n", failures, iters);
		nerrs++;
	} else {
		printf("[OK]\tAll %d iterations succeeded\n", iters);
	}
}