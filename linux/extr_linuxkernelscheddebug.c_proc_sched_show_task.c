#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  long long u64 ;
struct TYPE_6__ {scalar_t__ deadline; scalar_t__ runtime; } ;
struct TYPE_5__ {scalar_t__ weight; } ;
struct TYPE_8__ {int /*<<< orphan*/  nr_wakeups_idle; int /*<<< orphan*/  nr_wakeups_passive; int /*<<< orphan*/  nr_wakeups_affine_attempts; int /*<<< orphan*/  nr_wakeups_affine; int /*<<< orphan*/  nr_wakeups_remote; int /*<<< orphan*/  nr_wakeups_local; int /*<<< orphan*/  nr_wakeups_migrate; int /*<<< orphan*/  nr_wakeups_sync; int /*<<< orphan*/  nr_wakeups; int /*<<< orphan*/  nr_forced_migrations; int /*<<< orphan*/  nr_failed_migrations_hot; int /*<<< orphan*/  nr_failed_migrations_running; int /*<<< orphan*/  nr_failed_migrations_affine; int /*<<< orphan*/  nr_migrations_cold; int /*<<< orphan*/  iowait_count; int /*<<< orphan*/  iowait_sum; int /*<<< orphan*/  wait_count; int /*<<< orphan*/  wait_sum; int /*<<< orphan*/  wait_max; int /*<<< orphan*/  slice_max; int /*<<< orphan*/  exec_max; int /*<<< orphan*/  block_max; int /*<<< orphan*/  sleep_max; int /*<<< orphan*/  block_start; int /*<<< orphan*/  sleep_start; int /*<<< orphan*/  wait_start; int /*<<< orphan*/  sum_sleep_runtime; } ;
struct TYPE_7__ {long long sum_exec_runtime; scalar_t__ runnable_weight; TYPE_1__ load; scalar_t__ nr_migrations; TYPE_4__ statistics; scalar_t__ vruntime; scalar_t__ exec_start; } ;
struct task_struct {unsigned long nvcsw; unsigned long nivcsw; scalar_t__ policy; TYPE_2__ dl; scalar_t__ prio; TYPE_3__ se; int /*<<< orphan*/  comm; } ;
struct seq_file {int dummy; } ;
struct pid_namespace {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCHED_DEADLINE ; 
 int /*<<< orphan*/  SEQ_printf (struct seq_file*,char*,...) ; 
 long long SPLIT_NS (long long) ; 
 long long cpu_clock (unsigned int) ; 
 long long div64_u64 (long long,scalar_t__) ; 
 long long div64_ul (long long,unsigned long) ; 
 int /*<<< orphan*/  get_nr_threads (struct task_struct*) ; 
 unsigned int raw_smp_processor_id () ; 
 int /*<<< orphan*/  sched_show_numa (struct task_struct*,struct seq_file*) ; 
 scalar_t__ schedstat_enabled () ; 
 scalar_t__ schedstat_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr_ns (struct task_struct*,struct pid_namespace*) ; 

void proc_sched_show_task(struct task_struct *p, struct pid_namespace *ns,
						  struct seq_file *m)
{
	unsigned long nr_switches;

	SEQ_printf(m, "%s (%d, #threads: %d)\n", p->comm, task_pid_nr_ns(p, ns),
						get_nr_threads(p));
	SEQ_printf(m,
		"---------------------------------------------------------"
		"----------\n");
#define __P(F) \
	SEQ_printf(m, "%-45s:%21Ld\n", #F, (long long)F)
#define P(F) \
	SEQ_printf(m, "%-45s:%21Ld\n", #F, (long long)p->F)
#define P_SCHEDSTAT(F) \
	SEQ_printf(m, "%-45s:%21Ld\n", #F, (long long)schedstat_val(p->F))
#define __PN(F) \
	SEQ_printf(m, "%-45s:%14Ld.%06ld\n", #F, SPLIT_NS((long long)F))
#define PN(F) \
	SEQ_printf(m, "%-45s:%14Ld.%06ld\n", #F, SPLIT_NS((long long)p->F))
#define PN_SCHEDSTAT(F) \
	SEQ_printf(m, "%-45s:%14Ld.%06ld\n", #F, SPLIT_NS((long long)schedstat_val(p->F)))

	PN(se.exec_start);
	PN(se.vruntime);
	PN(se.sum_exec_runtime);

	nr_switches = p->nvcsw + p->nivcsw;

	P(se.nr_migrations);

	if (schedstat_enabled()) {
		u64 avg_atom, avg_per_cpu;

		PN_SCHEDSTAT(se.statistics.sum_sleep_runtime);
		PN_SCHEDSTAT(se.statistics.wait_start);
		PN_SCHEDSTAT(se.statistics.sleep_start);
		PN_SCHEDSTAT(se.statistics.block_start);
		PN_SCHEDSTAT(se.statistics.sleep_max);
		PN_SCHEDSTAT(se.statistics.block_max);
		PN_SCHEDSTAT(se.statistics.exec_max);
		PN_SCHEDSTAT(se.statistics.slice_max);
		PN_SCHEDSTAT(se.statistics.wait_max);
		PN_SCHEDSTAT(se.statistics.wait_sum);
		P_SCHEDSTAT(se.statistics.wait_count);
		PN_SCHEDSTAT(se.statistics.iowait_sum);
		P_SCHEDSTAT(se.statistics.iowait_count);
		P_SCHEDSTAT(se.statistics.nr_migrations_cold);
		P_SCHEDSTAT(se.statistics.nr_failed_migrations_affine);
		P_SCHEDSTAT(se.statistics.nr_failed_migrations_running);
		P_SCHEDSTAT(se.statistics.nr_failed_migrations_hot);
		P_SCHEDSTAT(se.statistics.nr_forced_migrations);
		P_SCHEDSTAT(se.statistics.nr_wakeups);
		P_SCHEDSTAT(se.statistics.nr_wakeups_sync);
		P_SCHEDSTAT(se.statistics.nr_wakeups_migrate);
		P_SCHEDSTAT(se.statistics.nr_wakeups_local);
		P_SCHEDSTAT(se.statistics.nr_wakeups_remote);
		P_SCHEDSTAT(se.statistics.nr_wakeups_affine);
		P_SCHEDSTAT(se.statistics.nr_wakeups_affine_attempts);
		P_SCHEDSTAT(se.statistics.nr_wakeups_passive);
		P_SCHEDSTAT(se.statistics.nr_wakeups_idle);

		avg_atom = p->se.sum_exec_runtime;
		if (nr_switches)
			avg_atom = div64_ul(avg_atom, nr_switches);
		else
			avg_atom = -1LL;

		avg_per_cpu = p->se.sum_exec_runtime;
		if (p->se.nr_migrations) {
			avg_per_cpu = div64_u64(avg_per_cpu,
						p->se.nr_migrations);
		} else {
			avg_per_cpu = -1LL;
		}

		__PN(avg_atom);
		__PN(avg_per_cpu);
	}

	__P(nr_switches);
	SEQ_printf(m, "%-45s:%21Ld\n",
		   "nr_voluntary_switches", (long long)p->nvcsw);
	SEQ_printf(m, "%-45s:%21Ld\n",
		   "nr_involuntary_switches", (long long)p->nivcsw);

	P(se.load.weight);
	P(se.runnable_weight);
#ifdef CONFIG_SMP
	P(se.avg.load_sum);
	P(se.avg.runnable_load_sum);
	P(se.avg.util_sum);
	P(se.avg.load_avg);
	P(se.avg.runnable_load_avg);
	P(se.avg.util_avg);
	P(se.avg.last_update_time);
	P(se.avg.util_est.ewma);
	P(se.avg.util_est.enqueued);
#endif
	P(policy);
	P(prio);
	if (p->policy == SCHED_DEADLINE) {
		P(dl.runtime);
		P(dl.deadline);
	}
#undef PN_SCHEDSTAT
#undef PN
#undef __PN
#undef P_SCHEDSTAT
#undef P
#undef __P

	{
		unsigned int this_cpu = raw_smp_processor_id();
		u64 t0, t1;

		t0 = cpu_clock(this_cpu);
		t1 = cpu_clock(this_cpu);
		SEQ_printf(m, "%-45s:%21Ld\n",
			   "clock-delta", (long long)(t1-t0));
	}

	sched_show_numa(p, m);
}