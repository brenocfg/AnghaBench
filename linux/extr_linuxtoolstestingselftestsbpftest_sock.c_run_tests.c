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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ run_test_case (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tests ; 

__attribute__((used)) static int run_tests(int cgfd)
{
	int passes = 0;
	int fails = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(tests); ++i) {
		if (run_test_case(cgfd, &tests[i]))
			++fails;
		else
			++passes;
	}
	printf("Summary: %d PASSED, %d FAILED\n", passes, fails);
	return fails ? -1 : 0;
}