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
 int /*<<< orphan*/  FUTEX_PRIVATE_FLAG ; 
 int /*<<< orphan*/  child_ret ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f1 ; 
 int /*<<< orphan*/  futex_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *blocking_child(void *arg)
{
	child_ret = futex_wait(&f1, f1, NULL, FUTEX_PRIVATE_FLAG);
	if (child_ret < 0) {
		child_ret = -errno;
		error("futex_wait\n", errno);
	}
	return (void *)&child_ret;
}