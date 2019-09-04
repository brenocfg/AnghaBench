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
struct sample_read_value {scalar_t__ value; int /*<<< orphan*/  id; } ;
struct perf_tool {int (* sample ) (struct perf_tool*,union perf_event*,struct perf_sample*,int /*<<< orphan*/ *,struct machine*) ;} ;
struct perf_sample_id {int /*<<< orphan*/ * evsel; scalar_t__ period; } ;
struct perf_sample {scalar_t__ period; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_unknown_id; } ;
struct perf_evlist {TYPE_1__ stats; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 struct perf_sample_id* perf_evlist__id2sid (struct perf_evlist*,int /*<<< orphan*/ ) ; 
 int stub1 (struct perf_tool*,union perf_event*,struct perf_sample*,int /*<<< orphan*/ *,struct machine*) ; 

__attribute__((used)) static int deliver_sample_value(struct perf_evlist *evlist,
				struct perf_tool *tool,
				union perf_event *event,
				struct perf_sample *sample,
				struct sample_read_value *v,
				struct machine *machine)
{
	struct perf_sample_id *sid = perf_evlist__id2sid(evlist, v->id);

	if (sid) {
		sample->id     = v->id;
		sample->period = v->value - sid->period;
		sid->period    = v->value;
	}

	if (!sid || sid->evsel == NULL) {
		++evlist->stats.nr_unknown_id;
		return 0;
	}

	return tool->sample(tool, event, sample, sid->evsel, machine);
}