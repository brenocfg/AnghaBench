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
struct iscsi_np {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int __iscsi_target_login_thread (struct iscsi_np*) ; 
 int /*<<< orphan*/  allow_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msleep (int) ; 

int iscsi_target_login_thread(void *arg)
{
	struct iscsi_np *np = arg;
	int ret;

	allow_signal(SIGINT);

	while (1) {
		ret = __iscsi_target_login_thread(np);
		/*
		 * We break and exit here unless another sock_accept() call
		 * is expected.
		 */
		if (ret != 1)
			break;
	}

	while (!kthread_should_stop()) {
		msleep(100);
	}

	return 0;
}