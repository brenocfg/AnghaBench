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
 int ATM_EXIT ; 
 int /*<<< orphan*/  MUTEX_DESTROY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFUNC () ; 
 int /*<<< orphan*/  allocator_thread ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_ips_lock ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * req_pipefd ; 
 int /*<<< orphan*/ * resp_pipefd ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int const*,int) ; 

void at_close(void) {
	PFUNC();
	const int msg = ATM_EXIT;
	write(req_pipefd[1], &msg, sizeof(int));
	pthread_join(allocator_thread, NULL);
	close(req_pipefd[0]);
	close(req_pipefd[1]);
	close(resp_pipefd[0]);
	close(resp_pipefd[1]);
	MUTEX_DESTROY(internal_ips_lock);
}