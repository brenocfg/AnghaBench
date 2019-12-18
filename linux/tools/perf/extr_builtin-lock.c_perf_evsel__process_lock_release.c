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
struct perf_sample {int dummy; } ;
struct evsel {int dummy; } ;
struct TYPE_2__ {int (* release_event ) (struct evsel*,struct perf_sample*) ;} ;

/* Variables and functions */
 int stub1 (struct evsel*,struct perf_sample*) ; 
 TYPE_1__* trace_handler ; 

__attribute__((used)) static int perf_evsel__process_lock_release(struct evsel *evsel,
					    struct perf_sample *sample)
{
	if (trace_handler->release_event)
		return trace_handler->release_event(evsel, sample);
	return 0;
}