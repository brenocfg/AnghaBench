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
struct tep_handle {int dummy; } ;
struct TYPE_2__ {scalar_t__ config; } ;
struct perf_evsel {struct event_format* tp_format; int /*<<< orphan*/ * name; TYPE_1__ attr; } ;
struct event_format {char* system; char* name; } ;
typedef  int /*<<< orphan*/  bf ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 struct event_format* tep_find_event (struct tep_handle*,scalar_t__) ; 

__attribute__((used)) static int perf_evsel__prepare_tracepoint_event(struct perf_evsel *evsel,
						struct tep_handle *pevent)
{
	struct event_format *event;
	char bf[128];

	/* already prepared */
	if (evsel->tp_format)
		return 0;

	if (pevent == NULL) {
		pr_debug("broken or missing trace data\n");
		return -1;
	}

	event = tep_find_event(pevent, evsel->attr.config);
	if (event == NULL) {
		pr_debug("cannot find event format for %d\n", (int)evsel->attr.config);
		return -1;
	}

	if (!evsel->name) {
		snprintf(bf, sizeof(bf), "%s:%s", event->system, event->name);
		evsel->name = strdup(bf);
		if (evsel->name == NULL)
			return -1;
	}

	evsel->tp_format = event;
	return 0;
}