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
struct perf_tool {int dummy; } ;
struct perf_evsel {int /*<<< orphan*/  name; int /*<<< orphan*/ * id; } ;
struct event_update_event {int /*<<< orphan*/  data; } ;
typedef  int (* perf_event__handler_t ) (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_EVENT_UPDATE__NAME ; 
 struct event_update_event* event_update_event__new (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct event_update_event*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

int
perf_event__synthesize_event_update_name(struct perf_tool *tool,
					 struct perf_evsel *evsel,
					 perf_event__handler_t process)
{
	struct event_update_event *ev;
	size_t len = strlen(evsel->name);
	int err;

	ev = event_update_event__new(len + 1, PERF_EVENT_UPDATE__NAME, evsel->id[0]);
	if (ev == NULL)
		return -ENOMEM;

	strncpy(ev->data, evsel->name, len);
	err = process(tool, (union perf_event*) ev, NULL, NULL);
	free(ev);
	return err;
}