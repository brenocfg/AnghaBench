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
struct thread {int dummy; } ;
struct perf_sched {scalar_t__ idle_hist; int /*<<< orphan*/  skipped_samples; } ;
struct perf_sample {int dummy; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 scalar_t__ perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  perf_evsel__name (struct evsel*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ thread__is_filtered (struct thread*) ; 

__attribute__((used)) static bool timehist_skip_sample(struct perf_sched *sched,
				 struct thread *thread,
				 struct evsel *evsel,
				 struct perf_sample *sample)
{
	bool rc = false;

	if (thread__is_filtered(thread)) {
		rc = true;
		sched->skipped_samples++;
	}

	if (sched->idle_hist) {
		if (strcmp(perf_evsel__name(evsel), "sched:sched_switch"))
			rc = true;
		else if (perf_evsel__intval(evsel, sample, "prev_pid") != 0 &&
			 perf_evsel__intval(evsel, sample, "next_pid") != 0)
			rc = true;
	}

	return rc;
}