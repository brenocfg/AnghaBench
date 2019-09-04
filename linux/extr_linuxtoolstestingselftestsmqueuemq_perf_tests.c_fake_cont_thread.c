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
 scalar_t__* cpu_threads ; 
 int* cpus_to_pin ; 
 int num_cpus_to_pin ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ pthread_self () ; 

void *fake_cont_thread(void *arg)
{
	int i;

	for (i = 0; i < num_cpus_to_pin; i++)
		if (cpu_threads[i] == pthread_self())
			break;
	printf("\tStarted fake continuous mode thread %d on CPU %d\n", i,
	       cpus_to_pin[i]);
	while (1)
		;
}