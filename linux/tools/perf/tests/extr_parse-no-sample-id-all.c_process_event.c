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
struct TYPE_2__ {scalar_t__ type; } ;
union perf_event {TYPE_1__ header; } ;
struct perf_sample {int dummy; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 scalar_t__ PERF_RECORD_HEADER_ATTR ; 
 scalar_t__ PERF_RECORD_USER_TYPE_START ; 
 scalar_t__ perf_event__process_attr (int /*<<< orphan*/ *,union perf_event*,struct evlist**) ; 
 scalar_t__ perf_evlist__parse_sample (struct evlist*,union perf_event*,struct perf_sample*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int process_event(struct evlist **pevlist, union perf_event *event)
{
	struct perf_sample sample;

	if (event->header.type == PERF_RECORD_HEADER_ATTR) {
		if (perf_event__process_attr(NULL, event, pevlist)) {
			pr_debug("perf_event__process_attr failed\n");
			return -1;
		}
		return 0;
	}

	if (event->header.type >= PERF_RECORD_USER_TYPE_START)
		return -1;

	if (!*pevlist)
		return -1;

	if (perf_evlist__parse_sample(*pevlist, event, &sample)) {
		pr_debug("perf_evlist__parse_sample failed\n");
		return -1;
	}

	return 0;
}