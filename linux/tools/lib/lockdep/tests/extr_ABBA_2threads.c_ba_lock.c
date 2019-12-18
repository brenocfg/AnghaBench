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
 scalar_t__ PTHREAD_BARRIER_SERIAL_THREAD ; 
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  bar ; 
 int /*<<< orphan*/  pthread_barrier_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void *ba_lock(void *arg)
{
	int ret, i;

	pthread_mutex_lock(&b);

	if (pthread_barrier_wait(&bar) == PTHREAD_BARRIER_SERIAL_THREAD)
		pthread_barrier_destroy(&bar);

	pthread_mutex_lock(&a);

	pthread_mutex_unlock(&a);
	pthread_mutex_unlock(&b);
}