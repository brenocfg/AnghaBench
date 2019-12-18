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
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_membarrier_thread_cond ; 
 int /*<<< orphan*/  test_membarrier_thread_mutex ; 
 int /*<<< orphan*/  thread_quit ; 
 int thread_ready ; 

void *test_membarrier_thread(void *arg)
{
	pthread_mutex_lock(&test_membarrier_thread_mutex);
	thread_ready = 1;
	pthread_cond_broadcast(&test_membarrier_thread_cond);
	pthread_mutex_unlock(&test_membarrier_thread_mutex);

	pthread_mutex_lock(&test_membarrier_thread_mutex);
	while (!thread_quit)
		pthread_cond_wait(&test_membarrier_thread_cond,
				  &test_membarrier_thread_mutex);
	pthread_mutex_unlock(&test_membarrier_thread_mutex);

	return NULL;
}