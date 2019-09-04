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
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bind_cpu(int cpu_num)
{
	cpu_set_t mask;

	CPU_ZERO(&mask);
	CPU_SET(cpu_num, &mask);

	/* bind my thread to cpu_num by assigning zero to the first argument */
	if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
		pr_err("Could not set CPU#%d affinity\n", (int)cpu_num);
}