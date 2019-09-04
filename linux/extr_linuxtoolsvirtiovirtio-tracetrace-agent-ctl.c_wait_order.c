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
struct pollfd {int fd; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_WAIT_MSEC ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  cond_wakeup ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_run_operation ; 
 int global_sig_receive ; 
 scalar_t__ global_signal_val ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wait_order(int ctl_fd)
{
	struct pollfd poll_fd;
	int ret = 0;

	while (!global_sig_receive) {
		poll_fd.fd = ctl_fd;
		poll_fd.events = POLLIN;

		ret = poll(&poll_fd, 1, EVENT_WAIT_MSEC);

		if (global_signal_val) {
			global_sig_receive = true;
			pr_info("Receive interrupt %d\n", global_signal_val);

			/* Wakes rw-threads when they are sleeping */
			if (!global_run_operation)
				pthread_cond_broadcast(&cond_wakeup);

			ret = -1;
			break;
		}

		if (ret < 0) {
			pr_err("Polling error\n");
			goto error;
		}

		if (ret)
			break;
	};

	return ret;

error:
	exit(EXIT_FAILURE);
}