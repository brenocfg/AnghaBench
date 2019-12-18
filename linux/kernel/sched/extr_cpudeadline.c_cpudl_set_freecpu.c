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
struct cpudl {int /*<<< orphan*/  free_cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 

void cpudl_set_freecpu(struct cpudl *cp, int cpu)
{
	cpumask_set_cpu(cpu, cp->free_cpus);
}