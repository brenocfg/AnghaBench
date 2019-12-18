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
struct timespec {unsigned long long tv_sec; void* tv_nsec; } ;
struct perf_counts_values {void* val; void* run; void* ena; } ;
struct evsel {scalar_t__ tool_event; int /*<<< orphan*/  counts; } ;

/* Variables and functions */
 scalar_t__ PERF_TOOL_DURATION_TIME ; 
 struct perf_counts_values* perf_counts (int /*<<< orphan*/ ,int,int) ; 
 int perf_evsel__read_counter (struct evsel*,int,int) ; 

__attribute__((used)) static int read_single_counter(struct evsel *counter, int cpu,
			       int thread, struct timespec *rs)
{
	if (counter->tool_event == PERF_TOOL_DURATION_TIME) {
		u64 val = rs->tv_nsec + rs->tv_sec*1000000000ULL;
		struct perf_counts_values *count =
			perf_counts(counter->counts, cpu, thread);
		count->ena = count->run = val;
		count->val = val;
		return 0;
	}
	return perf_evsel__read_counter(counter, cpu, thread);
}