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
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_membarrier_fail () ; 
 int /*<<< orphan*/  test_membarrier_success () ; 
 int /*<<< orphan*/  test_membarrier_thread ; 
 int /*<<< orphan*/  test_membarrier_thread_cond ; 
 int /*<<< orphan*/  test_membarrier_thread_mutex ; 
 int thread_quit ; 
 int /*<<< orphan*/  thread_ready ; 

__attribute__((used)) static int test_mt_membarrier(void)
{
	int i;
	pthread_t test_thread;

	pthread_create(&test_thread, NULL,
		       test_membarrier_thread, NULL);

	pthread_mutex_lock(&test_membarrier_thread_mutex);
	while (!thread_ready)
		pthread_cond_wait(&test_membarrier_thread_cond,
				  &test_membarrier_thread_mutex);
	pthread_mutex_unlock(&test_membarrier_thread_mutex);

	test_membarrier_fail();

	test_membarrier_success();

	pthread_mutex_lock(&test_membarrier_thread_mutex);
	thread_quit = 1;
	pthread_cond_broadcast(&test_membarrier_thread_cond);
	pthread_mutex_unlock(&test_membarrier_thread_mutex);

	pthread_join(test_thread, NULL);

	return 0;
}