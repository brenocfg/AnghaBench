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
 int MEMBARRIER_CMD_GLOBAL ; 
 int /*<<< orphan*/  MEMBARRIER_CMD_QUERY ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*) ; 
 int sys_membarrier (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_membarrier_query(void)
{
	int flags = 0, ret;

	ret = sys_membarrier(MEMBARRIER_CMD_QUERY, flags);
	if (ret < 0) {
		if (errno == ENOSYS) {
			/*
			 * It is valid to build a kernel with
			 * CONFIG_MEMBARRIER=n. However, this skips the tests.
			 */
			ksft_exit_skip(
				"sys membarrier (CONFIG_MEMBARRIER) is disabled.\n");
		}
		ksft_exit_fail_msg("sys_membarrier() failed\n");
	}
	if (!(ret & MEMBARRIER_CMD_GLOBAL))
		ksft_exit_skip(
			"sys_membarrier unsupported: CMD_GLOBAL not found.\n");

	ksft_test_result_pass("sys_membarrier available\n");
	return 0;
}