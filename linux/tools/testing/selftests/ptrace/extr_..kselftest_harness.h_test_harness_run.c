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
struct __test_metadata {scalar_t__ passed; struct __test_metadata* next; } ;

/* Variables and functions */
 int __fixture_count ; 
 int /*<<< orphan*/  __run_test (struct __test_metadata*) ; 
 int __test_count ; 
 struct __test_metadata* __test_list ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int test_harness_run(int __attribute__((unused)) argc,
			    char __attribute__((unused)) **argv)
{
	struct __test_metadata *t;
	int ret = 0;
	unsigned int count = 0;
	unsigned int pass_count = 0;

	/* TODO(wad) add optional arguments similar to gtest. */
	printf("[==========] Running %u tests from %u test cases.\n",
	       __test_count, __fixture_count + 1);
	for (t = __test_list; t; t = t->next) {
		count++;
		__run_test(t);
		if (t->passed)
			pass_count++;
		else
			ret = 1;
	}
	printf("[==========] %u / %u tests passed.\n", pass_count, count);
	printf("[  %s  ]\n", (ret ? "FAILED" : "PASSED"));
	return ret;
}