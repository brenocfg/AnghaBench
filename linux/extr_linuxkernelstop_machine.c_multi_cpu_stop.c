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
struct multi_stop_data {int state; int (* fn ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; int /*<<< orphan*/  active_cpus; } ;
typedef  enum multi_stop_state { ____Placeholder_multi_stop_state } multi_stop_state ;

/* Variables and functions */
#define  MULTI_STOP_DISABLE_IRQ 129 
 int MULTI_STOP_EXIT ; 
 int MULTI_STOP_NONE ; 
 int MULTI_STOP_PREPARE ; 
#define  MULTI_STOP_RUN 128 
 int /*<<< orphan*/  ack_state (struct multi_stop_data*) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpu_relax_yield () ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int smp_processor_id () ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_nmi_watchdog () ; 

__attribute__((used)) static int multi_cpu_stop(void *data)
{
	struct multi_stop_data *msdata = data;
	enum multi_stop_state curstate = MULTI_STOP_NONE;
	int cpu = smp_processor_id(), err = 0;
	unsigned long flags;
	bool is_active;

	/*
	 * When called from stop_machine_from_inactive_cpu(), irq might
	 * already be disabled.  Save the state and restore it on exit.
	 */
	local_save_flags(flags);

	if (!msdata->active_cpus)
		is_active = cpu == cpumask_first(cpu_online_mask);
	else
		is_active = cpumask_test_cpu(cpu, msdata->active_cpus);

	/* Simple state machine */
	do {
		/* Chill out and ensure we re-read multi_stop_state. */
		cpu_relax_yield();
		if (msdata->state != curstate) {
			curstate = msdata->state;
			switch (curstate) {
			case MULTI_STOP_DISABLE_IRQ:
				local_irq_disable();
				hard_irq_disable();
				break;
			case MULTI_STOP_RUN:
				if (is_active)
					err = msdata->fn(msdata->data);
				break;
			default:
				break;
			}
			ack_state(msdata);
		} else if (curstate > MULTI_STOP_PREPARE) {
			/*
			 * At this stage all other CPUs we depend on must spin
			 * in the same loop. Any reason for hard-lockup should
			 * be detected and reported on their side.
			 */
			touch_nmi_watchdog();
		}
	} while (curstate != MULTI_STOP_EXIT);

	local_irq_restore(flags);
	return err;
}