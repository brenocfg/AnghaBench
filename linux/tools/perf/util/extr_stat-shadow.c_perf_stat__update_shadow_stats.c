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
typedef  int /*<<< orphan*/  u64 ;
struct saved_value {int /*<<< orphan*/  metric_other; int /*<<< orphan*/  metric_total; int /*<<< orphan*/  stats; } ;
struct runtime_stat {int dummy; } ;
struct evsel {struct evsel* metric_leader; scalar_t__ collect_stat; int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  APERF ; 
 int /*<<< orphan*/  CYCLES_IN_TX ; 
 int /*<<< orphan*/  ELISION_START ; 
 int /*<<< orphan*/  HARDWARE ; 
 int /*<<< orphan*/  HW_BRANCH_INSTRUCTIONS ; 
 int /*<<< orphan*/  HW_CACHE ; 
 int /*<<< orphan*/  HW_CACHE_DTLB ; 
 int /*<<< orphan*/  HW_CACHE_ITLB ; 
 int /*<<< orphan*/  HW_CACHE_L1D ; 
 int /*<<< orphan*/  HW_CACHE_L1I ; 
 int /*<<< orphan*/  HW_CACHE_LL ; 
 int /*<<< orphan*/  HW_CACHE_REFERENCES ; 
 int /*<<< orphan*/  HW_CPU_CYCLES ; 
 int /*<<< orphan*/  HW_STALLED_CYCLES_BACKEND ; 
 int /*<<< orphan*/  HW_STALLED_CYCLES_FRONTEND ; 
 int /*<<< orphan*/  SMI_NUM ; 
 int /*<<< orphan*/  STAT_APERF ; 
 int /*<<< orphan*/  STAT_BRANCHES ; 
 int /*<<< orphan*/  STAT_CACHEREFS ; 
 int /*<<< orphan*/  STAT_CYCLES ; 
 int /*<<< orphan*/  STAT_CYCLES_IN_TX ; 
 int /*<<< orphan*/  STAT_DTLB_CACHE ; 
 int /*<<< orphan*/  STAT_ELISION ; 
 int /*<<< orphan*/  STAT_ITLB_CACHE ; 
 int /*<<< orphan*/  STAT_L1_DCACHE ; 
 int /*<<< orphan*/  STAT_L1_ICACHE ; 
 int /*<<< orphan*/  STAT_LL_CACHE ; 
 int /*<<< orphan*/  STAT_NONE ; 
 int /*<<< orphan*/  STAT_NSECS ; 
 int /*<<< orphan*/  STAT_SMI_NUM ; 
 int /*<<< orphan*/  STAT_STALLED_CYCLES_BACK ; 
 int /*<<< orphan*/  STAT_STALLED_CYCLES_FRONT ; 
 int /*<<< orphan*/  STAT_TOPDOWN_FETCH_BUBBLES ; 
 int /*<<< orphan*/  STAT_TOPDOWN_RECOVERY_BUBBLES ; 
 int /*<<< orphan*/  STAT_TOPDOWN_SLOTS_ISSUED ; 
 int /*<<< orphan*/  STAT_TOPDOWN_SLOTS_RETIRED ; 
 int /*<<< orphan*/  STAT_TOPDOWN_TOTAL_SLOTS ; 
 int /*<<< orphan*/  STAT_TRANSACTION ; 
 int /*<<< orphan*/  TOPDOWN_FETCH_BUBBLES ; 
 int /*<<< orphan*/  TOPDOWN_RECOVERY_BUBBLES ; 
 int /*<<< orphan*/  TOPDOWN_SLOTS_ISSUED ; 
 int /*<<< orphan*/  TOPDOWN_SLOTS_RETIRED ; 
 int /*<<< orphan*/  TOPDOWN_TOTAL_SLOTS ; 
 int /*<<< orphan*/  TRANSACTION_START ; 
 int evsel_context (struct evsel*) ; 
 scalar_t__ perf_evsel__is_clock (struct evsel*) ; 
 scalar_t__ perf_evsel__match (struct evsel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_stat_evsel__is (struct evsel*,int /*<<< orphan*/ ) ; 
 struct saved_value* saved_value_lookup (struct evsel*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct runtime_stat*) ; 
 int /*<<< orphan*/  update_runtime_stat (struct runtime_stat*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void perf_stat__update_shadow_stats(struct evsel *counter, u64 count,
				    int cpu, struct runtime_stat *st)
{
	int ctx = evsel_context(counter);
	u64 count_ns = count;
	struct saved_value *v;

	count *= counter->scale;

	if (perf_evsel__is_clock(counter))
		update_runtime_stat(st, STAT_NSECS, 0, cpu, count_ns);
	else if (perf_evsel__match(counter, HARDWARE, HW_CPU_CYCLES))
		update_runtime_stat(st, STAT_CYCLES, ctx, cpu, count);
	else if (perf_stat_evsel__is(counter, CYCLES_IN_TX))
		update_runtime_stat(st, STAT_CYCLES_IN_TX, ctx, cpu, count);
	else if (perf_stat_evsel__is(counter, TRANSACTION_START))
		update_runtime_stat(st, STAT_TRANSACTION, ctx, cpu, count);
	else if (perf_stat_evsel__is(counter, ELISION_START))
		update_runtime_stat(st, STAT_ELISION, ctx, cpu, count);
	else if (perf_stat_evsel__is(counter, TOPDOWN_TOTAL_SLOTS))
		update_runtime_stat(st, STAT_TOPDOWN_TOTAL_SLOTS,
				    ctx, cpu, count);
	else if (perf_stat_evsel__is(counter, TOPDOWN_SLOTS_ISSUED))
		update_runtime_stat(st, STAT_TOPDOWN_SLOTS_ISSUED,
				    ctx, cpu, count);
	else if (perf_stat_evsel__is(counter, TOPDOWN_SLOTS_RETIRED))
		update_runtime_stat(st, STAT_TOPDOWN_SLOTS_RETIRED,
				    ctx, cpu, count);
	else if (perf_stat_evsel__is(counter, TOPDOWN_FETCH_BUBBLES))
		update_runtime_stat(st, STAT_TOPDOWN_FETCH_BUBBLES,
				    ctx, cpu, count);
	else if (perf_stat_evsel__is(counter, TOPDOWN_RECOVERY_BUBBLES))
		update_runtime_stat(st, STAT_TOPDOWN_RECOVERY_BUBBLES,
				    ctx, cpu, count);
	else if (perf_evsel__match(counter, HARDWARE, HW_STALLED_CYCLES_FRONTEND))
		update_runtime_stat(st, STAT_STALLED_CYCLES_FRONT,
				    ctx, cpu, count);
	else if (perf_evsel__match(counter, HARDWARE, HW_STALLED_CYCLES_BACKEND))
		update_runtime_stat(st, STAT_STALLED_CYCLES_BACK,
				    ctx, cpu, count);
	else if (perf_evsel__match(counter, HARDWARE, HW_BRANCH_INSTRUCTIONS))
		update_runtime_stat(st, STAT_BRANCHES, ctx, cpu, count);
	else if (perf_evsel__match(counter, HARDWARE, HW_CACHE_REFERENCES))
		update_runtime_stat(st, STAT_CACHEREFS, ctx, cpu, count);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_L1D))
		update_runtime_stat(st, STAT_L1_DCACHE, ctx, cpu, count);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_L1I))
		update_runtime_stat(st, STAT_L1_ICACHE, ctx, cpu, count);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_LL))
		update_runtime_stat(st, STAT_LL_CACHE, ctx, cpu, count);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_DTLB))
		update_runtime_stat(st, STAT_DTLB_CACHE, ctx, cpu, count);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_ITLB))
		update_runtime_stat(st, STAT_ITLB_CACHE, ctx, cpu, count);
	else if (perf_stat_evsel__is(counter, SMI_NUM))
		update_runtime_stat(st, STAT_SMI_NUM, ctx, cpu, count);
	else if (perf_stat_evsel__is(counter, APERF))
		update_runtime_stat(st, STAT_APERF, ctx, cpu, count);

	if (counter->collect_stat) {
		v = saved_value_lookup(counter, cpu, true, STAT_NONE, 0, st);
		update_stats(&v->stats, count);
		if (counter->metric_leader)
			v->metric_total += count;
	} else if (counter->metric_leader) {
		v = saved_value_lookup(counter->metric_leader,
				       cpu, true, STAT_NONE, 0, st);
		v->metric_total += count;
		v->metric_other++;
	}
}