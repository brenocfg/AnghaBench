#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nr_cpus_online; } ;
struct TYPE_6__ {TYPE_4__ env; } ;
struct perf_session {TYPE_1__ header; struct evlist* evlist; } ;
struct TYPE_10__ {int ordered_events; int ordering_requires_timestamps; int /*<<< orphan*/  build_id; int /*<<< orphan*/  tracing_data; int /*<<< orphan*/  attr; int /*<<< orphan*/  lost; int /*<<< orphan*/  fork; int /*<<< orphan*/  exit; int /*<<< orphan*/  comm; int /*<<< orphan*/  mmap; int /*<<< orphan*/  sample; } ;
struct perf_sched {int max_cpu; scalar_t__ summary; int /*<<< orphan*/  nr_lost_chunks; int /*<<< orphan*/  nr_lost_events; int /*<<< orphan*/  nr_events; scalar_t__ summary_only; scalar_t__ show_migrations; int /*<<< orphan*/  time_str; int /*<<< orphan*/  ptime; TYPE_5__ tool; int /*<<< orphan*/  show_callchain; int /*<<< orphan*/  force; } ;
struct perf_data {int /*<<< orphan*/  force; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
struct evsel_str_handler {char* member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_7__ {int /*<<< orphan*/ * nr_events; int /*<<< orphan*/  total_lost; } ;
struct evlist {TYPE_2__ stats; } ;
struct TYPE_8__ {int /*<<< orphan*/  use_callchain; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  PERF_DATA_MODE_READ ; 
 size_t PERF_RECORD_LOST ; 
 int PTR_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  free_idle_threads () ; 
 scalar_t__ init_idle_threads (int) ; 
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  perf_event__process_attr ; 
 int /*<<< orphan*/  perf_event__process_build_id ; 
 int /*<<< orphan*/  perf_event__process_comm ; 
 int /*<<< orphan*/  perf_event__process_exit ; 
 int /*<<< orphan*/  perf_event__process_fork ; 
 int /*<<< orphan*/  perf_event__process_mmap ; 
 int /*<<< orphan*/  perf_event__process_tracing_data ; 
 int /*<<< orphan*/  perf_evlist__find_tracepoint_by_name (struct evlist*,char*) ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 struct perf_session* perf_session__new (struct perf_data*,int,TYPE_5__*) ; 
 int perf_session__process_events (struct perf_session*) ; 
 scalar_t__ perf_session__set_tracepoints_handlers (struct perf_session*,struct evsel_str_handler const*) ; 
 scalar_t__ perf_time__parse_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_timehist__process_sample ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  process_lost ; 
 int /*<<< orphan*/  setup_pager () ; 
 int /*<<< orphan*/  symbol__init (TYPE_4__*) ; 
 TYPE_3__ symbol_conf ; 
 scalar_t__ timehist_check_attr (struct perf_sched*,struct evlist*) ; 
 int /*<<< orphan*/  timehist_header (struct perf_sched*) ; 
 int /*<<< orphan*/  timehist_migrate_task_event ; 
 int /*<<< orphan*/  timehist_print_summary (struct perf_sched*,struct perf_session*) ; 
 int /*<<< orphan*/  timehist_sched_switch_event ; 
 int /*<<< orphan*/  timehist_sched_wakeup_event ; 

__attribute__((used)) static int perf_sched__timehist(struct perf_sched *sched)
{
	const struct evsel_str_handler handlers[] = {
		{ "sched:sched_switch",       timehist_sched_switch_event, },
		{ "sched:sched_wakeup",	      timehist_sched_wakeup_event, },
		{ "sched:sched_wakeup_new",   timehist_sched_wakeup_event, },
	};
	const struct evsel_str_handler migrate_handlers[] = {
		{ "sched:sched_migrate_task", timehist_migrate_task_event, },
	};
	struct perf_data data = {
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.force = sched->force,
	};

	struct perf_session *session;
	struct evlist *evlist;
	int err = -1;

	/*
	 * event handlers for timehist option
	 */
	sched->tool.sample	 = perf_timehist__process_sample;
	sched->tool.mmap	 = perf_event__process_mmap;
	sched->tool.comm	 = perf_event__process_comm;
	sched->tool.exit	 = perf_event__process_exit;
	sched->tool.fork	 = perf_event__process_fork;
	sched->tool.lost	 = process_lost;
	sched->tool.attr	 = perf_event__process_attr;
	sched->tool.tracing_data = perf_event__process_tracing_data;
	sched->tool.build_id	 = perf_event__process_build_id;

	sched->tool.ordered_events = true;
	sched->tool.ordering_requires_timestamps = true;

	symbol_conf.use_callchain = sched->show_callchain;

	session = perf_session__new(&data, false, &sched->tool);
	if (IS_ERR(session))
		return PTR_ERR(session);

	evlist = session->evlist;

	symbol__init(&session->header.env);

	if (perf_time__parse_str(&sched->ptime, sched->time_str) != 0) {
		pr_err("Invalid time string\n");
		return -EINVAL;
	}

	if (timehist_check_attr(sched, evlist) != 0)
		goto out;

	setup_pager();

	/* setup per-evsel handlers */
	if (perf_session__set_tracepoints_handlers(session, handlers))
		goto out;

	/* sched_switch event at a minimum needs to exist */
	if (!perf_evlist__find_tracepoint_by_name(session->evlist,
						  "sched:sched_switch")) {
		pr_err("No sched_switch events found. Have you run 'perf sched record'?\n");
		goto out;
	}

	if (sched->show_migrations &&
	    perf_session__set_tracepoints_handlers(session, migrate_handlers))
		goto out;

	/* pre-allocate struct for per-CPU idle stats */
	sched->max_cpu = session->header.env.nr_cpus_online;
	if (sched->max_cpu == 0)
		sched->max_cpu = 4;
	if (init_idle_threads(sched->max_cpu))
		goto out;

	/* summary_only implies summary option, but don't overwrite summary if set */
	if (sched->summary_only)
		sched->summary = sched->summary_only;

	if (!sched->summary_only)
		timehist_header(sched);

	err = perf_session__process_events(session);
	if (err) {
		pr_err("Failed to process events, error %d", err);
		goto out;
	}

	sched->nr_events      = evlist->stats.nr_events[0];
	sched->nr_lost_events = evlist->stats.total_lost;
	sched->nr_lost_chunks = evlist->stats.nr_events[PERF_RECORD_LOST];

	if (sched->summary)
		timehist_print_summary(sched, session);

out:
	free_idle_threads();
	perf_session__delete(session);

	return err;
}