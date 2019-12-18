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
struct perf_event_attr {unsigned long bp_addr; int /*<<< orphan*/  bp_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_BREAKPOINT_X ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_MODIFY_ATTRIBUTES ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct perf_event_attr*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 scalar_t__ test_function ; 
 int /*<<< orphan*/  the_var ; 
 int wp_event (void*,struct perf_event_attr*) ; 

__attribute__((used)) static int bp_accounting(int wp_cnt, int share)
{
	struct perf_event_attr attr, attr_mod, attr_new;
	int i, fd[wp_cnt], fd_wp, ret;

	for (i = 0; i < wp_cnt; i++) {
		fd[i] = wp_event((void *)&the_var, &attr);
		TEST_ASSERT_VAL("failed to create wp\n", fd[i] != -1);
		pr_debug("wp %d created\n", i);
	}

	attr_mod = attr;
	attr_mod.bp_type = HW_BREAKPOINT_X;
	attr_mod.bp_addr = (unsigned long) test_function;

	ret = ioctl(fd[0], PERF_EVENT_IOC_MODIFY_ATTRIBUTES, &attr_mod);
	TEST_ASSERT_VAL("failed to modify wp\n", ret == 0);

	pr_debug("wp 0 modified to bp\n");

	if (!share) {
		fd_wp = wp_event((void *)&the_var, &attr_new);
		TEST_ASSERT_VAL("failed to create max wp\n", fd_wp != -1);
		pr_debug("wp max created\n");
	}

	for (i = 0; i < wp_cnt; i++)
		close(fd[i]);

	return 0;
}