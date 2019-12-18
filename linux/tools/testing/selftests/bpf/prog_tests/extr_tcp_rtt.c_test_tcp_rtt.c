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
 scalar_t__ CHECK_FAIL (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int run_test (int,int) ; 
 int /*<<< orphan*/  server_started ; 
 int /*<<< orphan*/  server_started_mtx ; 
 int /*<<< orphan*/  server_thread ; 
 int start_server () ; 
 int test__join_cgroup (char*) ; 

void test_tcp_rtt(void)
{
	int server_fd, cgroup_fd;
	pthread_t tid;

	cgroup_fd = test__join_cgroup("/tcp_rtt");
	if (CHECK_FAIL(cgroup_fd < 0))
		return;

	server_fd = start_server();
	if (CHECK_FAIL(server_fd < 0))
		goto close_cgroup_fd;

	if (CHECK_FAIL(pthread_create(&tid, NULL, server_thread,
				      (void *)&server_fd)))
		goto close_server_fd;

	pthread_mutex_lock(&server_started_mtx);
	pthread_cond_wait(&server_started, &server_started_mtx);
	pthread_mutex_unlock(&server_started_mtx);

	CHECK_FAIL(run_test(cgroup_fd, server_fd));
close_server_fd:
	close(server_fd);
close_cgroup_fd:
	close(cgroup_fd);
}