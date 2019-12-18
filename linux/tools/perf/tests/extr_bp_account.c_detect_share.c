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
struct perf_event_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 int bp_event (void*,struct perf_event_attr*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ test_function ; 
 int /*<<< orphan*/  the_var ; 
 int wp_event (void*,struct perf_event_attr*) ; 

__attribute__((used)) static int detect_share(int wp_cnt, int bp_cnt)
{
	struct perf_event_attr attr;
	int i, fd[wp_cnt + bp_cnt], ret;

	for (i = 0; i < wp_cnt; i++) {
		fd[i] = wp_event((void *)&the_var, &attr);
		TEST_ASSERT_VAL("failed to create wp\n", fd[i] != -1);
	}

	for (; i < (bp_cnt + wp_cnt); i++) {
		fd[i] = bp_event((void *)test_function, &attr);
		if (fd[i] == -1)
			break;
	}

	ret = i != (bp_cnt + wp_cnt);

	while (i--)
		close(fd[i]);

	return ret;
}