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
 scalar_t__ ETIMEDOUT ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  RET_ERROR ; 
 int /*<<< orphan*/  TEST_NAME ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail (char*) ; 
 int futex_wait (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  print_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  val ; 
 int /*<<< orphan*/  wait_timeout ; 

void *thr_futex_wait(void *arg)
{
	int ret;

	info("futex wait\n");
	ret = futex_wait(&val, 1, &wait_timeout, 0);
	if (ret && errno != EWOULDBLOCK && errno != ETIMEDOUT) {
		error("futex error.\n", errno);
		print_result(TEST_NAME, RET_ERROR);
		exit(RET_ERROR);
	}

	if (ret && errno == ETIMEDOUT)
		fail("waiter timedout\n");

	info("futex_wait: ret = %d, errno = %d\n", ret, errno);

	return NULL;
}