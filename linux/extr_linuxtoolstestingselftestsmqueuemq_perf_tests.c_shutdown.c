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
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  __set (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__* cpu_threads ; 
 int errno ; 
 int /*<<< orphan*/  error (int,int,char*,char*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_msgs ; 
 int /*<<< orphan*/  max_msgsize ; 
 scalar_t__ mq_close (int) ; 
 int /*<<< orphan*/  mq_unlink (scalar_t__) ; 
 int num_cpus_to_pin ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_join (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int queue ; 
 scalar_t__ queue_path ; 
 scalar_t__ saved_max_msgs ; 
 scalar_t__ saved_max_msgsize ; 

void shutdown(int exit_val, char *err_cause, int line_no)
{
	static int in_shutdown = 0;
	int errno_at_shutdown = errno;
	int i;

	/* In case we get called by multiple threads or from an sighandler */
	if (in_shutdown++)
		return;

	for (i = 0; i < num_cpus_to_pin; i++)
		if (cpu_threads[i]) {
			pthread_kill(cpu_threads[i], SIGUSR1);
			pthread_join(cpu_threads[i], NULL);
		}

	if (queue != -1)
		if (mq_close(queue))
			perror("mq_close() during shutdown");
	if (queue_path)
		/*
		 * Be silent if this fails, if we cleaned up already it's
		 * expected to fail
		 */
		mq_unlink(queue_path);
	if (saved_max_msgs)
		__set(max_msgs, saved_max_msgs,
		      "failed to restore saved_max_msgs");
	if (saved_max_msgsize)
		__set(max_msgsize, saved_max_msgsize,
		      "failed to restore saved_max_msgsize");
	if (exit_val)
		error(exit_val, errno_at_shutdown, "%s at %d",
		      err_cause, line_no);
	exit(0);
}