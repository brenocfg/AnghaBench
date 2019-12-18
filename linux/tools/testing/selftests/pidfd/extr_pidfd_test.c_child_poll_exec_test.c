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
 int /*<<< orphan*/  SYS_gettid ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_pidfd_poll_exec_thread ; 

__attribute__((used)) static int child_poll_exec_test(void *args)
{
	pthread_t t1;

	ksft_print_msg("Child (pidfd): starting. pid %d tid %d\n", getpid(),
			syscall(SYS_gettid));
	pthread_create(&t1, NULL, test_pidfd_poll_exec_thread, NULL);
	/*
	 * Exec in the non-leader thread will destroy the leader immediately.
	 * If the wait in the parent returns too soon, the test fails.
	 */
	while (1)
		sleep(1);
}