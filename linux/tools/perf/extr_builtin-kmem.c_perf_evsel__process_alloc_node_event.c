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
struct perf_sample {int /*<<< orphan*/  cpu; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int cpu__get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_cross_allocs ; 
 int perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int perf_evsel__process_alloc_event (struct evsel*,struct perf_sample*) ; 

__attribute__((used)) static int perf_evsel__process_alloc_node_event(struct evsel *evsel,
						struct perf_sample *sample)
{
	int ret = perf_evsel__process_alloc_event(evsel, sample);

	if (!ret) {
		int node1 = cpu__get_node(sample->cpu),
		    node2 = perf_evsel__intval(evsel, sample, "node");

		if (node1 != node2)
			nr_cross_allocs++;
	}

	return ret;
}