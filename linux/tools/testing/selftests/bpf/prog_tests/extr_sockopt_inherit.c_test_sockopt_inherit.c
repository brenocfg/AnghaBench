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
 scalar_t__ CHECK_FAIL (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  run_test (int) ; 
 int test__join_cgroup (char*) ; 

void test_sockopt_inherit(void)
{
	int cgroup_fd;

	cgroup_fd = test__join_cgroup("/sockopt_inherit");
	if (CHECK_FAIL(cgroup_fd < 0))
		return;

	run_test(cgroup_fd);
	close(cgroup_fd);
}