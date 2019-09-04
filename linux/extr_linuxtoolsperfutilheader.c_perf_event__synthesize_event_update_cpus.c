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
typedef  union perf_event {int dummy; } perf_event ;
typedef  int /*<<< orphan*/  u16 ;
struct perf_tool {int dummy; } ;
struct perf_evsel {int /*<<< orphan*/  own_cpus; int /*<<< orphan*/ * id; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct event_update_event {scalar_t__ data; int /*<<< orphan*/  id; int /*<<< orphan*/  type; TYPE_1__ header; } ;
struct cpu_map_data {int dummy; } ;
typedef  int (* perf_event__handler_t ) (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_EVENT_UPDATE__CPUS ; 
 int /*<<< orphan*/  PERF_RECORD_EVENT_UPDATE ; 
 struct event_update_event* cpu_map_data__alloc (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  cpu_map_data__synthesize (struct cpu_map_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct event_update_event*) ; 

int
perf_event__synthesize_event_update_cpus(struct perf_tool *tool,
					struct perf_evsel *evsel,
					perf_event__handler_t process)
{
	size_t size = sizeof(struct event_update_event);
	struct event_update_event *ev;
	int max, err;
	u16 type;

	if (!evsel->own_cpus)
		return 0;

	ev = cpu_map_data__alloc(evsel->own_cpus, &size, &type, &max);
	if (!ev)
		return -ENOMEM;

	ev->header.type = PERF_RECORD_EVENT_UPDATE;
	ev->header.size = (u16)size;
	ev->type = PERF_EVENT_UPDATE__CPUS;
	ev->id   = evsel->id[0];

	cpu_map_data__synthesize((struct cpu_map_data *) ev->data,
				 evsel->own_cpus,
				 type, max);

	err = process(tool, (union perf_event*) ev, NULL, NULL);
	free(ev);
	return err;
}