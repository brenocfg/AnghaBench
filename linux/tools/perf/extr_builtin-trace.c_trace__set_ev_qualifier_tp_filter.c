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
struct TYPE_6__ {struct evsel* sys_exit; struct evsel* sys_enter; } ;
struct TYPE_5__ {TYPE_3__ events; } ;
struct TYPE_4__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  nr; } ;
struct trace {TYPE_2__ syscalls; TYPE_1__ ev_qualifier_ids; int /*<<< orphan*/  not_ev_qualifier; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 char* asprintf_expr_inout_ints (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int perf_evsel__append_tp_filter (struct evsel*,char*) ; 

__attribute__((used)) static int trace__set_ev_qualifier_tp_filter(struct trace *trace)
{
	int err = -1;
	struct evsel *sys_exit;
	char *filter = asprintf_expr_inout_ints("id", !trace->not_ev_qualifier,
						trace->ev_qualifier_ids.nr,
						trace->ev_qualifier_ids.entries);

	if (filter == NULL)
		goto out_enomem;

	if (!perf_evsel__append_tp_filter(trace->syscalls.events.sys_enter,
					  filter)) {
		sys_exit = trace->syscalls.events.sys_exit;
		err = perf_evsel__append_tp_filter(sys_exit, filter);
	}

	free(filter);
out:
	return err;
out_enomem:
	errno = ENOMEM;
	goto out;
}