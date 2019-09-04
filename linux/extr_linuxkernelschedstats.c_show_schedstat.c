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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcount; int /*<<< orphan*/  run_delay; } ;
struct rq {TYPE_1__ rq_sched_info; int /*<<< orphan*/  rq_cpu_time; int /*<<< orphan*/  ttwu_local; int /*<<< orphan*/  ttwu_count; int /*<<< orphan*/  sched_goidle; int /*<<< orphan*/  sched_count; int /*<<< orphan*/  yld_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHEDSTAT_VERSION ; 
 struct rq* cpu_rq (int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int show_schedstat(struct seq_file *seq, void *v)
{
	int cpu;

	if (v == (void *)1) {
		seq_printf(seq, "version %d\n", SCHEDSTAT_VERSION);
		seq_printf(seq, "timestamp %lu\n", jiffies);
	} else {
		struct rq *rq;
#ifdef CONFIG_SMP
		struct sched_domain *sd;
		int dcount = 0;
#endif
		cpu = (unsigned long)(v - 2);
		rq = cpu_rq(cpu);

		/* runqueue-specific stats */
		seq_printf(seq,
		    "cpu%d %u 0 %u %u %u %u %llu %llu %lu",
		    cpu, rq->yld_count,
		    rq->sched_count, rq->sched_goidle,
		    rq->ttwu_count, rq->ttwu_local,
		    rq->rq_cpu_time,
		    rq->rq_sched_info.run_delay, rq->rq_sched_info.pcount);

		seq_printf(seq, "\n");

#ifdef CONFIG_SMP
		/* domain-specific stats */
		rcu_read_lock();
		for_each_domain(cpu, sd) {
			enum cpu_idle_type itype;

			seq_printf(seq, "domain%d %*pb", dcount++,
				   cpumask_pr_args(sched_domain_span(sd)));
			for (itype = CPU_IDLE; itype < CPU_MAX_IDLE_TYPES;
					itype++) {
				seq_printf(seq, " %u %u %u %u %u %u %u %u",
				    sd->lb_count[itype],
				    sd->lb_balanced[itype],
				    sd->lb_failed[itype],
				    sd->lb_imbalance[itype],
				    sd->lb_gained[itype],
				    sd->lb_hot_gained[itype],
				    sd->lb_nobusyq[itype],
				    sd->lb_nobusyg[itype]);
			}
			seq_printf(seq,
				   " %u %u %u %u %u %u %u %u %u %u %u %u\n",
			    sd->alb_count, sd->alb_failed, sd->alb_pushed,
			    sd->sbe_count, sd->sbe_balanced, sd->sbe_pushed,
			    sd->sbf_count, sd->sbf_balanced, sd->sbf_pushed,
			    sd->ttwu_wake_remote, sd->ttwu_move_affine,
			    sd->ttwu_move_balance);
		}
		rcu_read_unlock();
#endif
	}
	return 0;
}