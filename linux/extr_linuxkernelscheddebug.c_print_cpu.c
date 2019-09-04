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
struct TYPE_2__ {int /*<<< orphan*/  weight; } ;
struct rq {int /*<<< orphan*/  ttwu_local; int /*<<< orphan*/  ttwu_count; int /*<<< orphan*/  sched_goidle; int /*<<< orphan*/  sched_count; int /*<<< orphan*/  yld_count; scalar_t__* cpu_load; int /*<<< orphan*/  clock_task; int /*<<< orphan*/  clock; int /*<<< orphan*/  curr; int /*<<< orphan*/  next_balance; scalar_t__ nr_uninterruptible; scalar_t__ nr_load_updates; scalar_t__ nr_switches; TYPE_1__ load; scalar_t__ nr_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  SPLIT_NS (int /*<<< orphan*/ ) ; 
 struct rq* cpu_rq (int) ; 
 int /*<<< orphan*/  print_cfs_stats (struct seq_file*,int) ; 
 int /*<<< orphan*/  print_dl_stats (struct seq_file*,int) ; 
 int /*<<< orphan*/  print_rq (struct seq_file*,struct rq*,int) ; 
 int /*<<< orphan*/  print_rt_stats (struct seq_file*,int) ; 
 int /*<<< orphan*/  sched_debug_lock ; 
 scalar_t__ schedstat_enabled () ; 
 int /*<<< orphan*/  schedstat_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_cpu(struct seq_file *m, int cpu)
{
	struct rq *rq = cpu_rq(cpu);
	unsigned long flags;

#ifdef CONFIG_X86
	{
		unsigned int freq = cpu_khz ? : 1;

		SEQ_printf(m, "cpu#%d, %u.%03u MHz\n",
			   cpu, freq / 1000, (freq % 1000));
	}
#else
	SEQ_printf(m, "cpu#%d\n", cpu);
#endif

#define P(x)								\
do {									\
	if (sizeof(rq->x) == 4)						\
		SEQ_printf(m, "  .%-30s: %ld\n", #x, (long)(rq->x));	\
	else								\
		SEQ_printf(m, "  .%-30s: %Ld\n", #x, (long long)(rq->x));\
} while (0)

#define PN(x) \
	SEQ_printf(m, "  .%-30s: %Ld.%06ld\n", #x, SPLIT_NS(rq->x))

	P(nr_running);
	SEQ_printf(m, "  .%-30s: %lu\n", "load",
		   rq->load.weight);
	P(nr_switches);
	P(nr_load_updates);
	P(nr_uninterruptible);
	PN(next_balance);
	SEQ_printf(m, "  .%-30s: %ld\n", "curr->pid", (long)(task_pid_nr(rq->curr)));
	PN(clock);
	PN(clock_task);
	P(cpu_load[0]);
	P(cpu_load[1]);
	P(cpu_load[2]);
	P(cpu_load[3]);
	P(cpu_load[4]);
#undef P
#undef PN

#ifdef CONFIG_SMP
#define P64(n) SEQ_printf(m, "  .%-30s: %Ld\n", #n, rq->n);
	P64(avg_idle);
	P64(max_idle_balance_cost);
#undef P64
#endif

#define P(n) SEQ_printf(m, "  .%-30s: %d\n", #n, schedstat_val(rq->n));
	if (schedstat_enabled()) {
		P(yld_count);
		P(sched_count);
		P(sched_goidle);
		P(ttwu_count);
		P(ttwu_local);
	}
#undef P

	spin_lock_irqsave(&sched_debug_lock, flags);
	print_cfs_stats(m, cpu);
	print_rt_stats(m, cpu);
	print_dl_stats(m, cpu);

	print_rq(m, rq, cpu);
	spin_unlock_irqrestore(&sched_debug_lock, flags);
	SEQ_printf(m, "\n");
}