#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct perf_tool {int ordered_events; int /*<<< orphan*/  namespaces; int /*<<< orphan*/  comm; int /*<<< orphan*/  sample; } ;
struct perf_data {int /*<<< orphan*/  force; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
struct TYPE_10__ {int /*<<< orphan*/  env; } ;
struct TYPE_11__ {TYPE_1__ header; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  PERF_DATA_MODE_READ ; 
 int PTR_ERR (TYPE_2__*) ; 
 int dump_info () ; 
 int /*<<< orphan*/  force ; 
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  lock_tracepoints ; 
 int /*<<< orphan*/  perf_event__process_comm ; 
 int /*<<< orphan*/  perf_event__process_namespaces ; 
 int /*<<< orphan*/  perf_session__delete (TYPE_2__*) ; 
 int /*<<< orphan*/  perf_session__has_traces (TYPE_2__*,char*) ; 
 TYPE_2__* perf_session__new (struct perf_data*,int,struct perf_tool*) ; 
 int perf_session__process_events (TYPE_2__*) ; 
 scalar_t__ perf_session__set_tracepoints_handlers (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_result () ; 
 int /*<<< orphan*/  process_sample_event ; 
 scalar_t__ select_key () ; 
 TYPE_2__* session ; 
 int /*<<< orphan*/  setup_pager () ; 
 int /*<<< orphan*/  sort_result () ; 
 int /*<<< orphan*/  symbol__init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __cmd_report(bool display_info)
{
	int err = -EINVAL;
	struct perf_tool eops = {
		.sample		 = process_sample_event,
		.comm		 = perf_event__process_comm,
		.namespaces	 = perf_event__process_namespaces,
		.ordered_events	 = true,
	};
	struct perf_data data = {
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.force = force,
	};

	session = perf_session__new(&data, false, &eops);
	if (IS_ERR(session)) {
		pr_err("Initializing perf session failed\n");
		return PTR_ERR(session);
	}

	symbol__init(&session->header.env);

	if (!perf_session__has_traces(session, "lock record"))
		goto out_delete;

	if (perf_session__set_tracepoints_handlers(session, lock_tracepoints)) {
		pr_err("Initializing perf session tracepoint handlers failed\n");
		goto out_delete;
	}

	if (select_key())
		goto out_delete;

	err = perf_session__process_events(session);
	if (err)
		goto out_delete;

	setup_pager();
	if (display_info) /* used for info subcommand */
		err = dump_info();
	else {
		sort_result();
		print_result();
	}

out_delete:
	perf_session__delete(session);
	return err;
}