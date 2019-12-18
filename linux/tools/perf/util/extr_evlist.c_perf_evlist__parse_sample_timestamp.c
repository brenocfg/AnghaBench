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
typedef  union perf_event {int dummy; } perf_event ;
typedef  int /*<<< orphan*/  u64 ;
struct evsel {int dummy; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 struct evsel* perf_evlist__event2evsel (struct evlist*,union perf_event*) ; 
 int perf_evsel__parse_sample_timestamp (struct evsel*,union perf_event*,int /*<<< orphan*/ *) ; 

int perf_evlist__parse_sample_timestamp(struct evlist *evlist,
					union perf_event *event,
					u64 *timestamp)
{
	struct evsel *evsel = perf_evlist__event2evsel(evlist, event);

	if (!evsel)
		return -EFAULT;
	return perf_evsel__parse_sample_timestamp(evsel, event, timestamp);
}