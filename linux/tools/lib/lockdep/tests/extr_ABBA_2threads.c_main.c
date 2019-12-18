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
 scalar_t__ PTHREAD_BARRIER_SERIAL_THREAD ; 
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  ba_lock ; 
 int /*<<< orphan*/  bar ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_barrier_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
	pthread_t t;

	pthread_barrier_init(&bar, NULL, 2);

	if (pthread_create(&t, NULL, ba_lock, NULL)) {
		fprintf(stderr, "pthread_create() failed\n");
		return 1;
	}
	pthread_mutex_lock(&a);

	if (pthread_barrier_wait(&bar) == PTHREAD_BARRIER_SERIAL_THREAD)
		pthread_barrier_destroy(&bar);

	pthread_mutex_lock(&b);

	pthread_mutex_unlock(&b);
	pthread_mutex_unlock(&a);

	pthread_join(t, NULL);

	return 0;
}