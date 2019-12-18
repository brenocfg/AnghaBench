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
typedef  void* u64 ;
struct perf_counts_values {void* run; void* ena; void* val; } ;
struct evsel {int /*<<< orphan*/  counts; } ;

/* Variables and functions */
 struct perf_counts_values* perf_counts (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  perf_counts__set_loaded (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
perf_evsel__set_count(struct evsel *counter, int cpu, int thread,
		      u64 val, u64 ena, u64 run)
{
	struct perf_counts_values *count;

	count = perf_counts(counter->counts, cpu, thread);

	count->val    = val;
	count->ena    = ena;
	count->run    = run;

	perf_counts__set_loaded(counter->counts, cpu, thread, true);
}