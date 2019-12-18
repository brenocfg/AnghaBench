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
struct TYPE_2__ {int /*<<< orphan*/  threads; } ;
struct evsel {TYPE_1__ core; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ perf_evsel__alloc_counts (struct evsel*,int,int) ; 
 scalar_t__ perf_evsel__alloc_prev_raw_counts (struct evsel*,int,int) ; 
 scalar_t__ perf_evsel__alloc_stat_priv (struct evsel*) ; 
 int perf_evsel__nr_cpus (struct evsel*) ; 
 int perf_thread_map__nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_evsel__alloc_stats(struct evsel *evsel, bool alloc_raw)
{
	int ncpus = perf_evsel__nr_cpus(evsel);
	int nthreads = perf_thread_map__nr(evsel->core.threads);

	if (perf_evsel__alloc_stat_priv(evsel) < 0 ||
	    perf_evsel__alloc_counts(evsel, ncpus, nthreads) < 0 ||
	    (alloc_raw && perf_evsel__alloc_prev_raw_counts(evsel, ncpus, nthreads) < 0))
		return -ENOMEM;

	return 0;
}