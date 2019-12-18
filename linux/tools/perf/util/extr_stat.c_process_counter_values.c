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
struct perf_stat_config {int aggr_mode; int /*<<< orphan*/ * stats; int /*<<< orphan*/  scale; } ;
struct perf_counts_values {int /*<<< orphan*/  run; int /*<<< orphan*/  ena; int /*<<< orphan*/  val; } ;
struct evsel {int /*<<< orphan*/  percore; int /*<<< orphan*/  snapshot; TYPE_1__* counts; } ;
struct TYPE_2__ {struct perf_counts_values aggr; } ;

/* Variables and functions */
#define  AGGR_CORE 134 
#define  AGGR_DIE 133 
#define  AGGR_GLOBAL 132 
#define  AGGR_NONE 131 
#define  AGGR_SOCKET 130 
#define  AGGR_THREAD 129 
#define  AGGR_UNSET 128 
 scalar_t__ check_per_pkg (struct evsel*,struct perf_counts_values*,int,int*) ; 
 int /*<<< orphan*/  perf_counts_values__scale (struct perf_counts_values*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_evsel__compute_deltas (struct evsel*,int,int,struct perf_counts_values*) ; 
 int /*<<< orphan*/  perf_stat__update_shadow_stats (struct evsel*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rt_stat ; 

__attribute__((used)) static int
process_counter_values(struct perf_stat_config *config, struct evsel *evsel,
		       int cpu, int thread,
		       struct perf_counts_values *count)
{
	struct perf_counts_values *aggr = &evsel->counts->aggr;
	static struct perf_counts_values zero;
	bool skip = false;

	if (check_per_pkg(evsel, count, cpu, &skip)) {
		pr_err("failed to read per-pkg counter\n");
		return -1;
	}

	if (skip)
		count = &zero;

	switch (config->aggr_mode) {
	case AGGR_THREAD:
	case AGGR_CORE:
	case AGGR_DIE:
	case AGGR_SOCKET:
	case AGGR_NONE:
		if (!evsel->snapshot)
			perf_evsel__compute_deltas(evsel, cpu, thread, count);
		perf_counts_values__scale(count, config->scale, NULL);
		if ((config->aggr_mode == AGGR_NONE) && (!evsel->percore)) {
			perf_stat__update_shadow_stats(evsel, count->val,
						       cpu, &rt_stat);
		}

		if (config->aggr_mode == AGGR_THREAD) {
			if (config->stats)
				perf_stat__update_shadow_stats(evsel,
					count->val, 0, &config->stats[thread]);
			else
				perf_stat__update_shadow_stats(evsel,
					count->val, 0, &rt_stat);
		}
		break;
	case AGGR_GLOBAL:
		aggr->val += count->val;
		aggr->ena += count->ena;
		aggr->run += count->run;
	case AGGR_UNSET:
	default:
		break;
	}

	return 0;
}