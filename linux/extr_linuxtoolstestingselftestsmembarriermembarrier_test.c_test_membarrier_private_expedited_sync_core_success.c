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
 int MEMBARRIER_CMD_PRIVATE_EXPEDITED ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*,char const*,int) ; 
 scalar_t__ sys_membarrier (int,int) ; 

__attribute__((used)) static int test_membarrier_private_expedited_sync_core_success(void)
{
	int cmd = MEMBARRIER_CMD_PRIVATE_EXPEDITED, flags = 0;
	const char *test_name = "sys membarrier MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE";

	if (sys_membarrier(cmd, flags) != 0) {
		ksft_exit_fail_msg(
			"%s test: flags = %d, errno = %d\n",
			test_name, flags, errno);
	}

	ksft_test_result_pass(
		"%s test: flags = %d\n",
		test_name, flags);
	return 0;
}