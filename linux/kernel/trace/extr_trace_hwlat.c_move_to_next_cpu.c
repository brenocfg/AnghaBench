#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpumask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpus_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (struct cpumask*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear (struct cpumask*) ; 
 int /*<<< orphan*/  cpumask_equal (struct cpumask*,int /*<<< orphan*/ ) ; 
 int cpumask_first (struct cpumask*) ; 
 int cpumask_next (int /*<<< orphan*/ ,struct cpumask*) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,struct cpumask*) ; 
 TYPE_1__* current ; 
 int disable_migrate ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 struct cpumask save_cpumask ; 
 int /*<<< orphan*/  sched_setaffinity (int /*<<< orphan*/ ,struct cpumask*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  tracing_buffer_mask ; 

__attribute__((used)) static void move_to_next_cpu(void)
{
	struct cpumask *current_mask = &save_cpumask;
	int next_cpu;

	if (disable_migrate)
		return;
	/*
	 * If for some reason the user modifies the CPU affinity
	 * of this thread, than stop migrating for the duration
	 * of the current test.
	 */
	if (!cpumask_equal(current_mask, current->cpus_ptr))
		goto disable;

	get_online_cpus();
	cpumask_and(current_mask, cpu_online_mask, tracing_buffer_mask);
	next_cpu = cpumask_next(smp_processor_id(), current_mask);
	put_online_cpus();

	if (next_cpu >= nr_cpu_ids)
		next_cpu = cpumask_first(current_mask);

	if (next_cpu >= nr_cpu_ids) /* Shouldn't happen! */
		goto disable;

	cpumask_clear(current_mask);
	cpumask_set_cpu(next_cpu, current_mask);

	sched_setaffinity(0, current_mask);
	return;

 disable:
	disable_migrate = true;
}