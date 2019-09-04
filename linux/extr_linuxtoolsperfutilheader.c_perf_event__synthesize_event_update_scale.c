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
struct perf_evsel {int /*<<< orphan*/  scale; int /*<<< orphan*/ * id; } ;
struct event_update_event_scale {int /*<<< orphan*/  scale; } ;
struct event_update_event {scalar_t__ data; } ;
typedef  int (* perf_event__handler_t ) (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_EVENT_UPDATE__SCALE ; 
 struct event_update_event* event_update_event__new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct event_update_event*) ; 

int
perf_event__synthesize_event_update_scale(struct perf_tool *tool,
					  struct perf_evsel *evsel,
					  perf_event__handler_t process)
{
	struct event_update_event *ev;
	struct event_update_event_scale *ev_data;
	int err;

	ev = event_update_event__new(sizeof(*ev_data), PERF_EVENT_UPDATE__SCALE, evsel->id[0]);
	if (ev == NULL)
		return -ENOMEM;

	ev_data = (struct event_update_event_scale *) ev->data;
	ev_data->scale = evsel->scale;
	err = process(tool, (union perf_event*) ev, NULL, NULL);
	free(ev);
	return err;
}