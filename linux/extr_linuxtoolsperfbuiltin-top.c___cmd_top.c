#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct sched_param {scalar_t__ sched_priority; } ;
struct record_opts {scalar_t__ overwrite; int /*<<< orphan*/  target; int /*<<< orphan*/  proc_map_timeout; } ;
struct TYPE_11__ {int /*<<< orphan*/  objdump_path; } ;
struct perf_top {int nr_threads_synthesize; scalar_t__ samples; TYPE_5__* session; struct perf_evlist* evlist; scalar_t__ realtime_prio; TYPE_2__ annotation_opts; struct record_opts record_opts; } ;
struct TYPE_13__ {int /*<<< orphan*/  drv_cfg; } ;
struct perf_evsel_config_term {TYPE_4__ val; } ;
struct perf_evsel {int dummy; } ;
struct perf_evlist {int /*<<< orphan*/  threads; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_15__ {scalar_t__ socket; } ;
struct TYPE_12__ {int /*<<< orphan*/  host; } ;
struct TYPE_10__ {int /*<<< orphan*/  env; } ;
struct TYPE_14__ {struct perf_evlist* evlist; TYPE_3__ machines; TYPE_1__ header; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  callchain_param ; 
 int callchain_param__setup_sample_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_thread ; 
 int /*<<< orphan*/  display_thread_tui ; 
 int /*<<< orphan*/  done ; 
 int errno ; 
 int /*<<< orphan*/  machine__synthesize_threads (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_env ; 
 int perf_env__lookup_objdump (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int perf_env__read_cpu_topology_map (int /*<<< orphan*/ *) ; 
 int perf_evlist__apply_drv_configs (struct perf_evlist*,struct perf_evsel**,struct perf_evsel_config_term**) ; 
 int /*<<< orphan*/  perf_evlist__enable (struct perf_evlist*) ; 
 int perf_evlist__poll (struct perf_evlist*,int) ; 
 int /*<<< orphan*/  perf_evsel__name (struct perf_evsel*) ; 
 TYPE_9__ perf_hpp_list ; 
 int /*<<< orphan*/  perf_session__delete (TYPE_5__*) ; 
 TYPE_5__* perf_session__new (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ perf_session__register_idle_thread (TYPE_5__*) ; 
 int /*<<< orphan*/  perf_session__set_id_hdr_size (TYPE_5__*) ; 
 int /*<<< orphan*/  perf_set_multithreaded () ; 
 int /*<<< orphan*/  perf_set_singlethreaded () ; 
 int /*<<< orphan*/  perf_top__mmap_read (struct perf_top*) ; 
 int /*<<< orphan*/  perf_top__resize (struct perf_top*) ; 
 int perf_top__start_counters (struct perf_top*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct perf_top*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ resize ; 
 scalar_t__ sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 char* str_error_r (int,char*,int) ; 
 int /*<<< orphan*/  target__none (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui__error (char*,...) ; 
 scalar_t__ use_browser ; 

__attribute__((used)) static int __cmd_top(struct perf_top *top)
{
	char msg[512];
	struct perf_evsel *pos;
	struct perf_evsel_config_term *err_term;
	struct perf_evlist *evlist = top->evlist;
	struct record_opts *opts = &top->record_opts;
	pthread_t thread;
	int ret;

	top->session = perf_session__new(NULL, false, NULL);
	if (top->session == NULL)
		return -1;

	if (!top->annotation_opts.objdump_path) {
		ret = perf_env__lookup_objdump(&top->session->header.env,
					       &top->annotation_opts.objdump_path);
		if (ret)
			goto out_delete;
	}

	ret = callchain_param__setup_sample_type(&callchain_param);
	if (ret)
		goto out_delete;

	if (perf_session__register_idle_thread(top->session) < 0)
		goto out_delete;

	if (top->nr_threads_synthesize > 1)
		perf_set_multithreaded();

	machine__synthesize_threads(&top->session->machines.host, &opts->target,
				    top->evlist->threads, false,
				    opts->proc_map_timeout,
				    top->nr_threads_synthesize);

	if (top->nr_threads_synthesize > 1)
		perf_set_singlethreaded();

	if (perf_hpp_list.socket) {
		ret = perf_env__read_cpu_topology_map(&perf_env);
		if (ret < 0)
			goto out_err_cpu_topo;
	}

	ret = perf_top__start_counters(top);
	if (ret)
		goto out_delete;

	ret = perf_evlist__apply_drv_configs(evlist, &pos, &err_term);
	if (ret) {
		pr_err("failed to set config \"%s\" on event %s with %d (%s)\n",
			err_term->val.drv_cfg, perf_evsel__name(pos), errno,
			str_error_r(errno, msg, sizeof(msg)));
		goto out_delete;
	}

	top->session->evlist = top->evlist;
	perf_session__set_id_hdr_size(top->session);

	/*
	 * When perf is starting the traced process, all the events (apart from
	 * group members) have enable_on_exec=1 set, so don't spoil it by
	 * prematurely enabling them.
	 *
	 * XXX 'top' still doesn't start workloads like record, trace, but should,
	 * so leave the check here.
	 */
        if (!target__none(&opts->target))
                perf_evlist__enable(top->evlist);

	/* Wait for a minimal set of events before starting the snapshot */
	perf_evlist__poll(top->evlist, 100);

	perf_top__mmap_read(top);

	ret = -1;
	if (pthread_create(&thread, NULL, (use_browser > 0 ? display_thread_tui :
							    display_thread), top)) {
		ui__error("Could not create display thread.\n");
		goto out_delete;
	}

	if (top->realtime_prio) {
		struct sched_param param;

		param.sched_priority = top->realtime_prio;
		if (sched_setscheduler(0, SCHED_FIFO, &param)) {
			ui__error("Could not set realtime priority.\n");
			goto out_join;
		}
	}

	while (!done) {
		u64 hits = top->samples;

		perf_top__mmap_read(top);

		if (opts->overwrite || (hits == top->samples))
			ret = perf_evlist__poll(top->evlist, 100);

		if (resize) {
			perf_top__resize(top);
			resize = 0;
		}
	}

	ret = 0;
out_join:
	pthread_join(thread, NULL);
out_delete:
	perf_session__delete(top->session);
	top->session = NULL;

	return ret;

out_err_cpu_topo: {
	char errbuf[BUFSIZ];
	const char *err = str_error_r(-ret, errbuf, sizeof(errbuf));

	ui__error("Could not read the CPU topology map: %s\n", err);
	goto out_delete;
}
}