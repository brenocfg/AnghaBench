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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int HOST_MSG_SIZE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  cond_wakeup ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int global_run_operation ; 
 int /*<<< orphan*/  global_sig_receive ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 
 int wait_order (int) ; 

void *rw_ctl_loop(int ctl_fd)
{
	ssize_t rlen;
	char buf[HOST_MSG_SIZE];
	int ret;

	/* Setup signal handlers */
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);

	while (!global_sig_receive) {

		ret = wait_order(ctl_fd);
		if (ret < 0)
			break;

		rlen = read(ctl_fd, buf, sizeof(buf));
		if (rlen < 0) {
			pr_err("read data error in ctl thread\n");
			goto error;
		}

		if (rlen == 2 && buf[0] == '1') {
			/*
			 * If host writes '1' to a control path,
			 * this controller wakes all read/write threads.
			 */
			global_run_operation = true;
			pthread_cond_broadcast(&cond_wakeup);
			pr_debug("Wake up all read/write threads\n");
		} else if (rlen == 2 && buf[0] == '0') {
			/*
			 * If host writes '0' to a control path, read/write
			 * threads will wait for notification from Host.
			 */
			global_run_operation = false;
			pr_debug("Stop all read/write threads\n");
		} else
			pr_info("Invalid host notification: %s\n", buf);
	}

	return NULL;

error:
	exit(EXIT_FAILURE);
}