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
struct seq_file {int dummy; } ;
struct rt_rq {int /*<<< orphan*/  rt_runtime; int /*<<< orphan*/  rt_time; scalar_t__ rt_throttled; scalar_t__ rt_nr_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_printf (struct seq_file*,char*,...) ; 
 long long SPLIT_NS (int /*<<< orphan*/ ) ; 

void print_rt_rq(struct seq_file *m, int cpu, struct rt_rq *rt_rq)
{
#ifdef CONFIG_RT_GROUP_SCHED
	SEQ_printf(m, "\n");
	SEQ_printf(m, "rt_rq[%d]:%s\n", cpu, task_group_path(rt_rq->tg));
#else
	SEQ_printf(m, "\n");
	SEQ_printf(m, "rt_rq[%d]:\n", cpu);
#endif

#define P(x) \
	SEQ_printf(m, "  .%-30s: %Ld\n", #x, (long long)(rt_rq->x))
#define PU(x) \
	SEQ_printf(m, "  .%-30s: %lu\n", #x, (unsigned long)(rt_rq->x))
#define PN(x) \
	SEQ_printf(m, "  .%-30s: %Ld.%06ld\n", #x, SPLIT_NS(rt_rq->x))

	PU(rt_nr_running);
#ifdef CONFIG_SMP
	PU(rt_nr_migratory);
#endif
	P(rt_throttled);
	PN(rt_time);
	PN(rt_runtime);

#undef PN
#undef PU
#undef P
}