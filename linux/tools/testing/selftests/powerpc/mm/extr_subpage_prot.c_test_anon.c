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
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_sigaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getpagesize () ; 
 int /*<<< orphan*/  posix_memalign (void**,int,unsigned long) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int run_test (void*,unsigned long) ; 
 int /*<<< orphan*/  segv ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  syscall_available () ; 

int test_anon(void)
{
	unsigned long align;
	struct sigaction act = {
		.sa_sigaction = segv,
		.sa_flags = SA_SIGINFO
	};
	void *mallocblock;
	unsigned long mallocsize;

	SKIP_IF(!syscall_available());

	if (getpagesize() != 0x10000) {
		fprintf(stderr, "Kernel page size must be 64K!\n");
		return 1;
	}

	sigaction(SIGSEGV, &act, NULL);

	mallocsize = 4 * 16 * 1024 * 1024;

	FAIL_IF(posix_memalign(&mallocblock, 64 * 1024, mallocsize));

	align = (unsigned long)mallocblock;
	if (align & 0xffff)
		align = (align | 0xffff) + 1;

	mallocblock = (void *)align;

	printf("allocated malloc block of 0x%lx bytes at %p\n",
	       mallocsize, mallocblock);

	printf("testing malloc block...\n");

	return run_test(mallocblock, mallocsize);
}