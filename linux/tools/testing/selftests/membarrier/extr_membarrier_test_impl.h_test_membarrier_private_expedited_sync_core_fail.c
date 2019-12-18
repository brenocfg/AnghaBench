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
 scalar_t__ EPERM ; 
 int MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,char const*,int,...) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*,char const*,int,scalar_t__) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int sys_membarrier (int,int) ; 

__attribute__((used)) static int test_membarrier_private_expedited_sync_core_fail(void)
{
	int cmd = MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE, flags = 0;
	const char *test_name = "sys membarrier MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE not registered failure";

	if (sys_membarrier(cmd, flags) != -1) {
		ksft_exit_fail_msg(
			"%s test: flags = %d. Should fail, but passed\n",
			test_name, flags);
	}
	if (errno != EPERM) {
		ksft_exit_fail_msg(
			"%s test: flags = %d. Should return (%d: \"%s\"), but returned (%d: \"%s\").\n",
			test_name, flags, EPERM, strerror(EPERM),
			errno, strerror(errno));
	}

	ksft_test_result_pass(
		"%s test: flags = %d, errno = %d\n",
		test_name, flags, errno);
	return 0;
}