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
 int /*<<< orphan*/  LOG_SIZE ; 
 int /*<<< orphan*/  check_ones (char*,size_t,char*) ; 
 int /*<<< orphan*/  check_ret (int,int) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int load (char*,size_t,int) ; 
 scalar_t__ memcmp (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int,size_t) ; 
 scalar_t__ strchr (char*,int) ; 
 size_t strnlen (char*,size_t) ; 

__attribute__((used)) static void test_log_good(char *log, size_t buf_len, size_t log_len,
			  size_t exp_len, int exp_errno, const char *full_log)
{
	size_t len;
	int ret;

	memset(log, 1, buf_len);

	ret = load(log, log_len, 1);
	check_ret(ret, exp_errno);

	len = strnlen(log, buf_len);
	if (len == buf_len) {
		err("verifier did not NULL terminate the log\n");
		exit(1);
	}
	if (exp_len && len != exp_len) {
		err("incorrect log length expected:%zd have:%zd\n",
		    exp_len, len);
		exit(1);
	}

	if (strchr(log, 1)) {
		err("verifier leaked a byte through\n");
		exit(1);
	}

	check_ones(log + len + 1, buf_len - len - 1,
		   "verifier wrote bytes past NULL termination\n");

	if (memcmp(full_log, log, LOG_SIZE)) {
		err("log did not match expected output\n");
		exit(1);
	}
}