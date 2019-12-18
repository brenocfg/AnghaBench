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
struct TYPE_4__ {int /*<<< orphan*/  env; } ;
struct perf_session {TYPE_3__* evlist; TYPE_1__ header; } ;
struct perf_sched {int /*<<< orphan*/  nr_lost_chunks; int /*<<< orphan*/  nr_lost_events; int /*<<< orphan*/  nr_events; int /*<<< orphan*/  tool; int /*<<< orphan*/  force; } ;
struct perf_data {int /*<<< orphan*/  force; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
struct evsel_str_handler {char* member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_5__ {int /*<<< orphan*/ * nr_events; int /*<<< orphan*/  total_lost; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  PERF_DATA_MODE_READ ; 
 size_t PERF_RECORD_LOST ; 
 int PTR_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 scalar_t__ perf_session__has_traces (struct perf_session*,char*) ; 
 struct perf_session* perf_session__new (struct perf_data*,int,int /*<<< orphan*/ *) ; 
 int perf_session__process_events (struct perf_session*) ; 
 scalar_t__ perf_session__set_tracepoints_handlers (struct perf_session*,struct evsel_str_handler const*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  process_sched_migrate_task_event ; 
 int /*<<< orphan*/  process_sched_runtime_event ; 
 int /*<<< orphan*/  process_sched_switch_event ; 
 int /*<<< orphan*/  process_sched_wakeup_event ; 
 int /*<<< orphan*/  symbol__init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_sched__read_events(struct perf_sched *sched)
{
	const struct evsel_str_handler handlers[] = {
		{ "sched:sched_switch",	      process_sched_switch_event, },
		{ "sched:sched_stat_runtime", process_sched_runtime_event, },
		{ "sched:sched_wakeup",	      process_sched_wakeup_event, },
		{ "sched:sched_wakeup_new",   process_sched_wakeup_event, },
		{ "sched:sched_migrate_task", process_sched_migrate_task_event, },
	};
	struct perf_session *session;
	struct perf_data data = {
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.force = sched->force,
	};
	int rc = -1;

	session = perf_session__new(&data, false, &sched->tool);
	if (IS_ERR(session)) {
		pr_debug("Error creating perf session");
		return PTR_ERR(session);
	}

	symbol__init(&session->header.env);

	if (perf_session__set_tracepoints_handlers(session, handlers))
		goto out_delete;

	if (perf_session__has_traces(session, "record -R")) {
		int err = perf_session__process_events(session);
		if (err) {
			pr_err("Failed to process events, error %d", err);
			goto out_delete;
		}

		sched->nr_events      = session->evlist->stats.nr_events[0];
		sched->nr_lost_events = session->evlist->stats.total_lost;
		sched->nr_lost_chunks = session->evlist->stats.nr_events[PERF_RECORD_LOST];
	}

	rc = 0;
out_delete:
	perf_session__delete(session);
	return rc;
}