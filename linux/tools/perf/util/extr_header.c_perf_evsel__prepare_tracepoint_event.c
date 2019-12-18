#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tep_handle {int dummy; } ;
struct tep_event {char* system; char* name; } ;
struct TYPE_3__ {scalar_t__ config; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {struct tep_event* tp_format; int /*<<< orphan*/ * name; TYPE_2__ core; } ;
typedef  int /*<<< orphan*/  bf ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 struct tep_event* tep_find_event (struct tep_handle*,scalar_t__) ; 

__attribute__((used)) static int perf_evsel__prepare_tracepoint_event(struct evsel *evsel,
						struct tep_handle *pevent)
{
	struct tep_event *event;
	char bf[128];

	/* already prepared */
	if (evsel->tp_format)
		return 0;

	if (pevent == NULL) {
		pr_debug("broken or missing trace data\n");
		return -1;
	}

	event = tep_find_event(pevent, evsel->core.attr.config);
	if (event == NULL) {
		pr_debug("cannot find event format for %d\n", (int)evsel->core.attr.config);
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