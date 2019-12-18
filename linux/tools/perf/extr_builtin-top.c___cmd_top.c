#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct sched_param {scalar_t__ sched_priority; } ;
struct record_opts {scalar_t__ overwrite; int /*<<< orphan*/  target; scalar_t__ record_namespaces; } ;
struct TYPE_19__ {int /*<<< orphan*/  cond; } ;
struct TYPE_16__ {int namespace_events; } ;
struct TYPE_15__ {int /*<<< orphan*/  objdump_path; } ;
struct perf_top {int nr_threads_synthesize; scalar_t__ samples; TYPE_6__ qe; TYPE_11__* evlist; scalar_t__ realtime_prio; TYPE_7__* session; struct record_opts record_opts; TYPE_3__ tool; TYPE_2__ annotation_opts; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_21__ {scalar_t__ socket; } ;
struct TYPE_17__ {int /*<<< orphan*/  host; } ;
struct TYPE_14__ {int /*<<< orphan*/  env; } ;
struct TYPE_20__ {TYPE_11__* evlist; TYPE_4__ machines; TYPE_1__ header; } ;
struct TYPE_18__ {int /*<<< orphan*/  threads; } ;
struct TYPE_13__ {TYPE_5__ core; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  callchain_param ; 
 int callchain_param__setup_sample_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_thread ; 
 int /*<<< orphan*/  display_thread_tui ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  evlist__enable (TYPE_11__*) ; 
 int evlist__poll (TYPE_11__*,int) ; 
 int /*<<< orphan*/  init_process_thread (struct perf_top*) ; 
 int /*<<< orphan*/  machine__synthesize_threads (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  perf_env ; 
 int perf_env__lookup_objdump (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int perf_env__read_cpu_topology_map (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event__process ; 
 int perf_event__synthesize_bpf_events (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct record_opts*) ; 
 TYPE_9__ perf_hpp_list ; 
 scalar_t__ perf_session__register_idle_thread (TYPE_7__*) ; 
 int /*<<< orphan*/  perf_session__set_id_hdr_size (TYPE_7__*) ; 
 int /*<<< orphan*/  perf_set_multithreaded () ; 
 int /*<<< orphan*/  perf_set_singlethreaded () ; 
 int /*<<< orphan*/  perf_top__mmap_read (struct perf_top*) ; 
 int /*<<< orphan*/  perf_top__resize (struct perf_top*) ; 
 int perf_top__start_counters (struct perf_top*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  process_thread ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
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
	struct record_opts *opts = &top->record_opts;
	pthread_t thread, thread_process;
	int ret;

	if (!top->annotation_opts.objdump_path) {
		ret = perf_env__lookup_objdump(&top->session->header.env,
					       &top->annotation_opts.objdump_path);
		if (ret)
			return ret;
	}

	ret = callchain_param__setup_sample_type(&callchain_param);
	if (ret)
		return ret;

	if (perf_session__register_idle_thread(top->session) < 0)
		return ret;

	if (top->nr_threads_synthesize > 1)
		perf_set_multithreaded();

	init_process_thread(top);

	if (opts->record_namespaces)
		top->tool.namespace_events = true;

	ret = perf_event__synthesize_bpf_events(top->session, perf_event__process,
						&top->session->machines.host,
						&top->record_opts);
	if (ret < 0)
		pr_debug("Couldn't synthesize BPF events: Pre-existing BPF programs won't have symbols resolved.\n");

	machine__synthesize_threads(&top->session->machines.host, &opts->target,
				    top->evlist->core.threads, false,
				    top->nr_threads_synthesize);

	if (top->nr_threads_synthesize > 1)
		perf_set_singlethreaded();

	if (perf_hpp_list.socket) {
		ret = perf_env__read_cpu_topology_map(&perf_env);
		if (ret < 0) {
			char errbuf[BUFSIZ];
			const char *err = str_error_r(-ret, errbuf, sizeof(errbuf));

			ui__error("Could not read the CPU topology map: %s\n", err);
			return ret;
		}
	}

	ret = perf_top__start_counters(top);
	if (ret)
		return ret;

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
		evlist__enable(top->evlist);

	ret = -1;
	if (pthread_create(&thread_process, NULL, process_thread, top)) {
		ui__error("Could not create process thread.\n");
		return ret;
	}

	if (pthread_create(&thread, NULL, (use_browser > 0 ? display_thread_tui :
							    display_thread), top)) {
		ui__error("Could not create display thread.\n");
		goto out_join_thread;
	}

	if (top->realtime_prio) {
		struct sched_param param;

		param.sched_priority = top->realtime_prio;
		if (sched_setscheduler(0, SCHED_FIFO, &param)) {
			ui__error("Could not set realtime priority.\n");
			goto out_join;
		}
	}

	/* Wait for a minimal set of events before starting the snapshot */
	evlist__poll(top->evlist, 100);

	perf_top__mmap_read(top);

	while (!done) {
		u64 hits = top->samples;

		perf_top__mmap_read(top);

		if (opts->overwrite || (hits == top->samples))
			ret = evlist__poll(top->evlist, 100);

		if (resize) {
			perf_top__resize(top);
			resize = 0;
		}
	}

	ret = 0;
out_join:
	pthread_join(thread, NULL);
out_join_thread:
	pthread_cond_signal(&top->qe.cond);
	pthread_join(thread_process, NULL);
	return ret;
}