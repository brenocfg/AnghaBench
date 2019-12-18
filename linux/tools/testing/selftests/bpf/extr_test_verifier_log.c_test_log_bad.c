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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOG_SIZE ; 
 int /*<<< orphan*/  check_ones (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_ret (int,int /*<<< orphan*/ ) ; 
 int load (char*,size_t,int) ; 

__attribute__((used)) static void test_log_bad(char *log, size_t log_len, int log_level)
{
	int ret;

	ret = load(log, log_len, log_level);
	check_ret(ret, EINVAL);
	if (log)
		check_ones(log, LOG_SIZE,
			   "verifier touched log with bad parameters\n");
}