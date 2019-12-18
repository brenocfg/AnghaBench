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
 scalar_t__ ENOSYS ; 
 int X32_BIT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ nerrs ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ syscall (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_x32_without_x32_bit () ; 

int main()
{
	/*
	 * Anyone diagnosing a failure will want to know whether the kernel
	 * supports x32.  Tell them.
	 */
	printf("\tChecking for x32...");
	fflush(stdout);
	if (syscall(39 | X32_BIT, 0, 0, 0, 0, 0, 0) >= 0) {
		printf(" supported\n");
	} else if (errno == ENOSYS) {
		printf(" not supported\n");
	} else {
		printf(" confused\n");
	}

	test_x32_without_x32_bit();

	return nerrs ? 1 : 0;
}