#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  descr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ CHECK_FAIL (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int run_test (int,TYPE_1__*) ; 
 int test__join_cgroup (char*) ; 
 int /*<<< orphan*/  test__start_subtest (int /*<<< orphan*/ ) ; 
 TYPE_1__* tests ; 

void test_sockopt(void)
{
	int cgroup_fd, i;

	cgroup_fd = test__join_cgroup("/sockopt");
	if (CHECK_FAIL(cgroup_fd < 0))
		return;

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		test__start_subtest(tests[i].descr);
		CHECK_FAIL(run_test(cgroup_fd, &tests[i]));
	}

	close(cgroup_fd);
}