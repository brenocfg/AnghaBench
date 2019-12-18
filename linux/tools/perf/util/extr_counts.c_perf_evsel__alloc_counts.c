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
struct evsel {int /*<<< orphan*/ * counts; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * perf_counts__new (int,int) ; 

int perf_evsel__alloc_counts(struct evsel *evsel, int ncpus, int nthreads)
{
	evsel->counts = perf_counts__new(ncpus, nthreads);
	return evsel->counts != NULL ? 0 : -ENOMEM;
}