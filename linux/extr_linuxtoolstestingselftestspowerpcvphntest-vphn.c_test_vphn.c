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
struct test {scalar_t__ descr; } ;

/* Variables and functions */
 struct test* all_tests ; 
 int /*<<< orphan*/  test_finish (scalar_t__,int) ; 
 int test_one (struct test*) ; 

__attribute__((used)) static int test_vphn(void)
{
	static struct test *test;

	for (test = all_tests; test->descr; test++) {
		int ret;

		ret = test_one(test);
		test_finish(test->descr, ret);
		if (ret)
			return ret;
	}

	return 0;
}