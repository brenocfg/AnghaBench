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
 int /*<<< orphan*/  CHILD_THREAD_MIN_WAIT ; 
 int /*<<< orphan*/  SYS_gettid ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *test_pidfd_poll_leader_exit_thread(void *priv)
{
	ksft_print_msg("Child Thread: starting. pid %d tid %d ; and sleeping\n",
			getpid(), syscall(SYS_gettid));
	sleep(CHILD_THREAD_MIN_WAIT);
	ksft_print_msg("Child Thread: DONE. pid %d tid %d\n", getpid(), syscall(SYS_gettid));
	return NULL;
}