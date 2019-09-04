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
struct trace {scalar_t__ base_time; int /*<<< orphan*/  full_time; } ;
struct perf_sample {scalar_t__ time; } ;
struct TYPE_2__ {int sample_type; } ;
struct perf_evsel {TYPE_1__ attr; } ;

/* Variables and functions */
 int PERF_SAMPLE_TIME ; 

__attribute__((used)) static void trace__set_base_time(struct trace *trace,
				 struct perf_evsel *evsel,
				 struct perf_sample *sample)
{
	/*
	 * BPF events were not setting PERF_SAMPLE_TIME, so be more robust
	 * and don't use sample->time unconditionally, we may end up having
	 * some other event in the future without PERF_SAMPLE_TIME for good
	 * reason, i.e. we may not be interested in its timestamps, just in
	 * it taking place, picking some piece of information when it
	 * appears in our event stream (vfs_getname comes to mind).
	 */
	if (trace->base_time == 0 && !trace->full_time &&
	    (evsel->attr.sample_type & PERF_SAMPLE_TIME))
		trace->base_time = sample->time;
}