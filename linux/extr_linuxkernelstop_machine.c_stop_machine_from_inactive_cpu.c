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
struct multi_stop_data {void* data; scalar_t__ num_threads; struct cpumask const* active_cpus; int /*<<< orphan*/  fn; } ;
struct cpumask {int dummy; } ;
struct cpu_stop_done {int ret; int /*<<< orphan*/  completion; } ;
typedef  int /*<<< orphan*/  cpu_stop_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MULTI_STOP_PREPARE ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_active_mask ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpu_stop_init_done (struct cpu_stop_done*,scalar_t__) ; 
 int multi_cpu_stop (struct multi_stop_data*) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ num_active_cpus () ; 
 int /*<<< orphan*/  queue_stop_cpus_work (int /*<<< orphan*/ ,int (*) (struct multi_stop_data*),struct multi_stop_data*,struct cpu_stop_done*) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  set_state (struct multi_stop_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_cpus_mutex ; 

int stop_machine_from_inactive_cpu(cpu_stop_fn_t fn, void *data,
				  const struct cpumask *cpus)
{
	struct multi_stop_data msdata = { .fn = fn, .data = data,
					    .active_cpus = cpus };
	struct cpu_stop_done done;
	int ret;

	/* Local CPU must be inactive and CPU hotplug in progress. */
	BUG_ON(cpu_active(raw_smp_processor_id()));
	msdata.num_threads = num_active_cpus() + 1;	/* +1 for local */

	/* No proper task established and can't sleep - busy wait for lock. */
	while (!mutex_trylock(&stop_cpus_mutex))
		cpu_relax();

	/* Schedule work on other CPUs and execute directly for local CPU */
	set_state(&msdata, MULTI_STOP_PREPARE);
	cpu_stop_init_done(&done, num_active_cpus());
	queue_stop_cpus_work(cpu_active_mask, multi_cpu_stop, &msdata,
			     &done);
	ret = multi_cpu_stop(&msdata);

	/* Busy wait for completion. */
	while (!completion_done(&done.completion))
		cpu_relax();

	mutex_unlock(&stop_cpus_mutex);
	return ret ?: done.ret;
}