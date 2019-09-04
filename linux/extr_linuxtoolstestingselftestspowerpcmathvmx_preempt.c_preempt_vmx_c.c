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
 int /*<<< orphan*/  preempt_vmx (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  running ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  threads_starting ; 
 int /*<<< orphan*/ ** varray ; 

void *preempt_vmx_c(void *p)
{
	int i, j;
	srand(pthread_self());
	for (i = 0; i < 12; i++)
		for (j = 0; j < 4; j++)
			varray[i][j] = rand();

	/* Test fails if it ever returns */
	preempt_vmx(varray, &threads_starting, &running);
	return p;
}