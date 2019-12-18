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

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  clearhandler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sethandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsegv_for_fallthrough ; 
 int /*<<< orphan*/  sigusr1 ; 
 int /*<<< orphan*/  test_sigreturn_to (unsigned long) ; 
 int /*<<< orphan*/  test_syscall_fallthrough_to (unsigned long) ; 

int main()
{
	/*
	 * When the kernel returns from a slow-path syscall, it will
	 * detect whether SYSRET is appropriate.  If it incorrectly
	 * thinks that SYSRET is appropriate when RIP is noncanonical,
	 * it'll crash on Intel CPUs.
	 */
	sethandler(SIGUSR1, sigusr1, 0);
	for (int i = 47; i < 64; i++)
		test_sigreturn_to(1UL<<i);

	clearhandler(SIGUSR1);

	sethandler(SIGSEGV, sigsegv_for_fallthrough, 0);

	/* One extra test to check that we didn't screw up the mremap logic. */
	test_syscall_fallthrough_to((1UL << 47) - 2*PAGE_SIZE);

	/* These are the interesting cases. */
	for (int i = 47; i < 64; i++) {
		test_syscall_fallthrough_to((1UL<<i) - PAGE_SIZE);
		test_syscall_fallthrough_to(1UL<<i);
	}

	return 0;
}