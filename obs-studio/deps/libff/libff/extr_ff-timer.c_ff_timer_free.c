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
struct ff_timer {int abort; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutexattr; int /*<<< orphan*/  mutex; int /*<<< orphan*/  timer_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 

void ff_timer_free(struct ff_timer *timer)
{
	void *thread_result;

	assert(timer != NULL);

	pthread_mutex_lock(&timer->mutex);
	timer->abort = true;
	pthread_cond_signal(&timer->cond);
	pthread_mutex_unlock(&timer->mutex);

	pthread_join(timer->timer_thread, &thread_result);

	pthread_mutex_destroy(&timer->mutex);
	pthread_mutexattr_destroy(&timer->mutexattr);
	pthread_cond_destroy(&timer->cond);
}