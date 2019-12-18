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
struct perf_counts_values {int dummy; } ;
struct evsel {int /*<<< orphan*/  core; int /*<<< orphan*/  counts; } ;

/* Variables and functions */
 struct perf_counts_values* perf_counts (int /*<<< orphan*/ ,int,int) ; 
 int perf_evsel__read (int /*<<< orphan*/ *,int,int,struct perf_counts_values*) ; 

__attribute__((used)) static int
perf_evsel__read_one(struct evsel *evsel, int cpu, int thread)
{
	struct perf_counts_values *count = perf_counts(evsel->counts, cpu, thread);

	return perf_evsel__read(&evsel->core, cpu, thread, count);
}