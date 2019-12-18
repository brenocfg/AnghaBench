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
struct perf_counts_values {int dummy; } ;
struct evsel {int /*<<< orphan*/ * counts; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FD (struct evsel*,int,int) ; 
 int errno ; 
 struct perf_counts_values* perf_counts (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  perf_counts_values__scale (struct perf_counts_values*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ perf_evsel__alloc_counts (struct evsel*,int,int) ; 
 int /*<<< orphan*/  perf_evsel__compute_deltas (struct evsel*,int,int,struct perf_counts_values*) ; 
 scalar_t__ readn (scalar_t__,struct perf_counts_values*,size_t) ; 

int __perf_evsel__read_on_cpu(struct evsel *evsel,
			      int cpu, int thread, bool scale)
{
	struct perf_counts_values count;
	size_t nv = scale ? 3 : 1;

	if (FD(evsel, cpu, thread) < 0)
		return -EINVAL;

	if (evsel->counts == NULL && perf_evsel__alloc_counts(evsel, cpu + 1, thread + 1) < 0)
		return -ENOMEM;

	if (readn(FD(evsel, cpu, thread), &count, nv * sizeof(u64)) <= 0)
		return -errno;

	perf_evsel__compute_deltas(evsel, cpu, thread, &count);
	perf_counts_values__scale(&count, scale, NULL);
	*perf_counts(evsel->counts, cpu, thread) = count;
	return 0;
}