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
struct multi_stop_data {int (* fn ) (void*) ;void* data; int num_threads; struct cpumask const* active_cpus; } ;
struct cpumask {int dummy; } ;
typedef  int (* cpu_stop_fn_t ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  MULTI_STOP_PREPARE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  lockdep_assert_cpus_held () ; 
 int /*<<< orphan*/  multi_cpu_stop ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  set_state (struct multi_stop_data*,int /*<<< orphan*/ ) ; 
 int stop_cpus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct multi_stop_data*) ; 
 int /*<<< orphan*/  stop_machine_initialized ; 
 int stub1 (void*) ; 

int stop_machine_cpuslocked(cpu_stop_fn_t fn, void *data,
			    const struct cpumask *cpus)
{
	struct multi_stop_data msdata = {
		.fn = fn,
		.data = data,
		.num_threads = num_online_cpus(),
		.active_cpus = cpus,
	};

	lockdep_assert_cpus_held();

	if (!stop_machine_initialized) {
		/*
		 * Handle the case where stop_machine() is called
		 * early in boot before stop_machine() has been
		 * initialized.
		 */
		unsigned long flags;
		int ret;

		WARN_ON_ONCE(msdata.num_threads != 1);

		local_irq_save(flags);
		hard_irq_disable();
		ret = (*fn)(data);
		local_irq_restore(flags);

		return ret;
	}

	/* Set the initial state and stop all online cpus. */
	set_state(&msdata, MULTI_STOP_PREPARE);
	return stop_cpus(cpu_online_mask, multi_cpu_stop, &msdata);
}