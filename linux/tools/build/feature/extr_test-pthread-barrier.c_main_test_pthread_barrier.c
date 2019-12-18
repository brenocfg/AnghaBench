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
typedef  int /*<<< orphan*/  pthread_barrier_t ;

/* Variables and functions */
 int pthread_barrier_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 

int main(void)
{
	pthread_barrier_t barrier;

	pthread_barrier_init(&barrier, NULL, 1);
	pthread_barrier_wait(&barrier);
	return pthread_barrier_destroy(&barrier);
}