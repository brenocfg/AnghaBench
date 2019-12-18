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
struct perf_counts {int dummy; } ;
struct evsel {struct perf_counts* prev_raw_counts; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct perf_counts* perf_counts__new (int,int) ; 

__attribute__((used)) static int perf_evsel__alloc_prev_raw_counts(struct evsel *evsel,
					     int ncpus, int nthreads)
{
	struct perf_counts *counts;

	counts = perf_counts__new(ncpus, nthreads);
	if (counts)
		evsel->prev_raw_counts = counts;

	return counts ? 0 : -ENOMEM;
}