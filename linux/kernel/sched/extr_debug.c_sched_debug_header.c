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
typedef  int /*<<< orphan*/  u64 ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; int /*<<< orphan*/  release; } ;

/* Variables and functions */
 int /*<<< orphan*/  P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_printf (struct seq_file*,char*,...) ; 
 TYPE_1__* init_utsname () ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_clock () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sched_clock () ; 
 int /*<<< orphan*/  sched_clock_stable () ; 
 int /*<<< orphan*/ * sched_tunable_scaling_names ; 
 scalar_t__ strcspn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sysctl_sched_child_runs_first ; 
 int /*<<< orphan*/  sysctl_sched_features ; 
 int /*<<< orphan*/  sysctl_sched_latency ; 
 int /*<<< orphan*/  sysctl_sched_min_granularity ; 
 size_t sysctl_sched_tunable_scaling ; 
 int /*<<< orphan*/  sysctl_sched_wakeup_granularity ; 

__attribute__((used)) static void sched_debug_header(struct seq_file *m)
{
	u64 ktime, sched_clk, cpu_clk;
	unsigned long flags;

	local_irq_save(flags);
	ktime = ktime_to_ns(ktime_get());
	sched_clk = sched_clock();
	cpu_clk = local_clock();
	local_irq_restore(flags);

	SEQ_printf(m, "Sched Debug Version: v0.11, %s %.*s\n",
		init_utsname()->release,
		(int)strcspn(init_utsname()->version, " "),
		init_utsname()->version);

#define P(x) \
	SEQ_printf(m, "%-40s: %Ld\n", #x, (long long)(x))
#define PN(x) \
	SEQ_printf(m, "%-40s: %Ld.%06ld\n", #x, SPLIT_NS(x))
	PN(ktime);
	PN(sched_clk);
	PN(cpu_clk);
	P(jiffies);
#ifdef CONFIG_HAVE_UNSTABLE_SCHED_CLOCK
	P(sched_clock_stable());
#endif
#undef PN
#undef P

	SEQ_printf(m, "\n");
	SEQ_printf(m, "sysctl_sched\n");

#define P(x) \
	SEQ_printf(m, "  .%-40s: %Ld\n", #x, (long long)(x))
#define PN(x) \
	SEQ_printf(m, "  .%-40s: %Ld.%06ld\n", #x, SPLIT_NS(x))
	PN(sysctl_sched_latency);
	PN(sysctl_sched_min_granularity);
	PN(sysctl_sched_wakeup_granularity);
	P(sysctl_sched_child_runs_first);
	P(sysctl_sched_features);
#undef PN
#undef P

	SEQ_printf(m, "  .%-40s: %d (%s)\n",
		"sysctl_sched_tunable_scaling",
		sysctl_sched_tunable_scaling,
		sched_tunable_scaling_names[sysctl_sched_tunable_scaling]);
	SEQ_printf(m, "\n");
}