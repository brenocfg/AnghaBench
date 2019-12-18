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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_exit ; 
 int /*<<< orphan*/  SYS_gettid ; 
 int /*<<< orphan*/ * child_exit_secs ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  test_pidfd_poll_leader_exit_thread ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int child_poll_leader_exit_test(void *args)
{
	pthread_t t1, t2;

	ksft_print_msg("Child: starting. pid %d tid %d\n", getpid(), syscall(SYS_gettid));
	pthread_create(&t1, NULL, test_pidfd_poll_leader_exit_thread, NULL);
	pthread_create(&t2, NULL, test_pidfd_poll_leader_exit_thread, NULL);

	/*
	 * glibc exit calls exit_group syscall, so explicity call exit only
	 * so that only the group leader exits, leaving the threads alone.
	 */
	*child_exit_secs = time(NULL);
	syscall(SYS_exit, 0);
}