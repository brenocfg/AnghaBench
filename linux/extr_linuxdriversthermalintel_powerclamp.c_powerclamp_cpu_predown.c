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
 int clamping ; 
 unsigned int control_cpu ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 unsigned int cpumask_first (int /*<<< orphan*/ ) ; 
 unsigned int cpumask_next (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  stop_power_clamp_worker (unsigned int) ; 

__attribute__((used)) static int powerclamp_cpu_predown(unsigned int cpu)
{
	if (clamping == false)
		return 0;

	stop_power_clamp_worker(cpu);
	if (cpu != control_cpu)
		return 0;

	control_cpu = cpumask_first(cpu_online_mask);
	if (control_cpu == cpu)
		control_cpu = cpumask_next(cpu, cpu_online_mask);
	smp_mb();
	return 0;
}