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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  barrier ; 
 scalar_t__ pthread_barrier_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_barrier_wait (int /*<<< orphan*/ *) ; 

int
main()
{
  assert(pthread_barrier_init(&barrier, NULL, 1) == 0);

  assert(pthread_barrier_wait(&barrier) == PTHREAD_BARRIER_SERIAL_THREAD);

  assert(pthread_barrier_destroy(&barrier) == 0);

  return 0;
}