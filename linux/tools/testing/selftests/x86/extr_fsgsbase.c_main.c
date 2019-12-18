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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUTEX_WAKE ; 
#define  HARD_ZERO 128 
 int MAP_ANONYMOUS ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SYS_futex ; 
 int /*<<< orphan*/  check_gs_value (int) ; 
 int /*<<< orphan*/  clearhandler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ftx ; 
 int have_fsgsbase ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mov_0_gs (int,int) ; 
 scalar_t__ nerrs ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdfsbase () ; 
 scalar_t__ sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_gs_and_switch_to (unsigned long,unsigned short,unsigned long) ; 
 int /*<<< orphan*/  sethandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shared_scratch ; 
 int /*<<< orphan*/  sigill ; 
 int /*<<< orphan*/  sigsegv ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ptrace_write_gsbase () ; 
 int /*<<< orphan*/  test_unexpected_base () ; 
 int /*<<< orphan*/  test_wrbase (unsigned short,int) ; 
 int /*<<< orphan*/  threadproc ; 

int main()
{
	pthread_t thread;

	shared_scratch = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
			      MAP_ANONYMOUS | MAP_SHARED, -1, 0);

	/* Probe FSGSBASE */
	sethandler(SIGILL, sigill, 0);
	if (sigsetjmp(jmpbuf, 1) == 0) {
		rdfsbase();
		have_fsgsbase = true;
		printf("\tFSGSBASE instructions are enabled\n");
	} else {
		printf("\tFSGSBASE instructions are disabled\n");
	}
	clearhandler(SIGILL);

	sethandler(SIGSEGV, sigsegv, 0);

	check_gs_value(0);
	check_gs_value(1);
	check_gs_value(0x200000000);
	check_gs_value(0);
	check_gs_value(0x200000000);
	check_gs_value(1);

	for (int sched = 0; sched < 2; sched++) {
		mov_0_gs(0, !!sched);
		mov_0_gs(1, !!sched);
		mov_0_gs(0x200000000, !!sched);
	}

	/* Set up for multithreading. */

	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0)
		err(1, "sched_setaffinity to CPU 0");	/* should never fail */

	if (pthread_create(&thread, 0, threadproc, 0) != 0)
		err(1, "pthread_create");

	static unsigned long bases_with_hard_zero[] = {
		0, HARD_ZERO, 1, 0x200000000,
	};

	for (int local = 0; local < 4; local++) {
		for (int remote = 0; remote < 4; remote++) {
			for (unsigned short s = 0; s < 5; s++) {
				unsigned short sel = s;
				if (s == 4)
					asm ("mov %%ss, %0" : "=rm" (sel));
				set_gs_and_switch_to(
					bases_with_hard_zero[local],
					sel,
					bases_with_hard_zero[remote]);
			}
		}
	}

	test_unexpected_base();

	if (have_fsgsbase) {
		unsigned short ss;

		asm volatile ("mov %%ss, %0" : "=rm" (ss));

		test_wrbase(0, 0);
		test_wrbase(0, 1);
		test_wrbase(0, 0x200000000);
		test_wrbase(0, 0xffffffffffffffff);
		test_wrbase(ss, 0);
		test_wrbase(ss, 1);
		test_wrbase(ss, 0x200000000);
		test_wrbase(ss, 0xffffffffffffffff);
	}

	ftx = 3;  /* Kill the thread. */
	syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, NULL, NULL, 0);

	if (pthread_join(thread, NULL) != 0)
		err(1, "pthread_join");

	test_ptrace_write_gsbase();

	return nerrs == 0 ? 0 : 1;
}