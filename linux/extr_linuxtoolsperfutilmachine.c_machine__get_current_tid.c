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
struct machine {int* current_tid; } ;
typedef  int pid_t ;

/* Variables and functions */
 int MAX_NR_CPUS ; 

pid_t machine__get_current_tid(struct machine *machine, int cpu)
{
	if (cpu < 0 || cpu >= MAX_NR_CPUS || !machine->current_tid)
		return -1;

	return machine->current_tid[cpu];
}