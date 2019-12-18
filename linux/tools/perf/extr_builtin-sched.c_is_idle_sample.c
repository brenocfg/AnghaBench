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
struct perf_sample {scalar_t__ pid; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 scalar_t__ perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  perf_evsel__name (struct evsel*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool is_idle_sample(struct perf_sample *sample,
			   struct evsel *evsel)
{
	/* pid 0 == swapper == idle task */
	if (strcmp(perf_evsel__name(evsel), "sched:sched_switch") == 0)
		return perf_evsel__intval(evsel, sample, "prev_pid") == 0;

	return sample->pid == 0;
}