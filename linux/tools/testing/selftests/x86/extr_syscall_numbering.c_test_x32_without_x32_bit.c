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
 int X32_BIT ; 
 int /*<<< orphan*/  check_enosys (int,int*) ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void test_x32_without_x32_bit(void)
{
	bool ok = true;

	/*
	 * Syscalls 512-547 are "x32" syscalls.  They are intended to be
	 * called with the x32 (0x40000000) bit set.  Calling them without
	 * the x32 bit set is nonsense and should not work.
	 */
	printf("[RUN]\tChecking syscalls 512-547\n");
	for (int i = 512; i <= 547; i++)
		check_enosys(i, &ok);

	/*
	 * Check that a handful of 64-bit-only syscalls are rejected if the x32
	 * bit is set.
	 */
	printf("[RUN]\tChecking some 64-bit syscalls in x32 range\n");
	check_enosys(16 | X32_BIT, &ok);	/* ioctl */
	check_enosys(19 | X32_BIT, &ok);	/* readv */
	check_enosys(20 | X32_BIT, &ok);	/* writev */

	/*
	 * Check some syscalls with high bits set.
	 */
	printf("[RUN]\tChecking numbers above 2^32-1\n");
	check_enosys((1UL << 32), &ok);
	check_enosys(X32_BIT | (1UL << 32), &ok);

	if (!ok)
		nerrs++;
	else
		printf("[OK]\tThey all returned -ENOSYS\n");
}