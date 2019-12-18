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
typedef  union perf_event {int dummy; } perf_event ;
struct tables {int /*<<< orphan*/  dbe; int /*<<< orphan*/  db_export_mode; } ;
struct perf_sample {int dummy; } ;
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
#define  PERF_TYPE_TRACEPOINT 128 
 int /*<<< orphan*/  db_export__sample (int /*<<< orphan*/ *,union perf_event*,struct perf_sample*,struct evsel*,struct addr_location*) ; 
 int /*<<< orphan*/  python_process_general_event (struct perf_sample*,struct evsel*,struct addr_location*) ; 
 int /*<<< orphan*/  python_process_tracepoint (struct perf_sample*,struct evsel*,struct addr_location*) ; 
 struct tables tables_global ; 

__attribute__((used)) static void python_process_event(union perf_event *event,
				 struct perf_sample *sample,
				 struct evsel *evsel,
				 struct addr_location *al)
{
	struct tables *tables = &tables_global;

	switch (evsel->core.attr.type) {
	case PERF_TYPE_TRACEPOINT:
		python_process_tracepoint(sample, evsel, al);
		break;
	/* Reserve for future process_hw/sw/raw APIs */
	default:
		if (tables->db_export_mode)
			db_export__sample(&tables->dbe, event, sample, evsel, al);
		else
			python_process_general_event(sample, evsel, al);
	}
}