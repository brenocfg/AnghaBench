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
 int /*<<< orphan*/ * darray ; 
 int /*<<< orphan*/  preempt_fpu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  running ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  threads_starting ; 

void *preempt_fpu_c(void *p)
{
	int i;
	srand(pthread_self());
	for (i = 0; i < 21; i++)
		darray[i] = rand();

	/* Test failed if it ever returns */
	preempt_fpu(darray, &threads_starting, &running);

	return p;
}