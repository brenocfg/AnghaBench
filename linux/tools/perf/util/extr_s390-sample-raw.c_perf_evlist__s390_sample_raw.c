#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; } ;
union perf_event {TYPE_1__ header; } ;
struct perf_sample {int dummy; } ;
struct TYPE_5__ {scalar_t__ config; } ;
struct TYPE_6__ {TYPE_2__ attr; } ;
struct evsel {TYPE_3__ core; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_CPUM_CF_DIAG ; 
 scalar_t__ PERF_RECORD_SAMPLE ; 
 struct evsel* perf_evlist__event2evsel (struct evlist*,union perf_event*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  s390_cpumcfdg_dump (struct perf_sample*) ; 
 int /*<<< orphan*/  s390_cpumcfdg_testctr (struct perf_sample*) ; 

void perf_evlist__s390_sample_raw(struct evlist *evlist, union perf_event *event,
				  struct perf_sample *sample)
{
	struct evsel *ev_bc000;

	if (event->header.type != PERF_RECORD_SAMPLE)
		return;

	ev_bc000 = perf_evlist__event2evsel(evlist, event);
	if (ev_bc000 == NULL ||
	    ev_bc000->core.attr.config != PERF_EVENT_CPUM_CF_DIAG)
		return;

	/* Display raw data on screen */
	if (!s390_cpumcfdg_testctr(sample)) {
		pr_err("Invalid counter set data encountered\n");
		return;
	}
	s390_cpumcfdg_dump(sample);
}