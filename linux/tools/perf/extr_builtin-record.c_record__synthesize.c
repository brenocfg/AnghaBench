#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct record_opts {int tail_synthesize; int /*<<< orphan*/  sample_address; int /*<<< orphan*/  target; scalar_t__ full_auxtrace; } ;
struct perf_tool {int dummy; } ;
struct perf_data {scalar_t__ is_pipe; } ;
struct record {int bytes_written; TYPE_2__* evlist; struct perf_tool tool; int /*<<< orphan*/  itr; struct record_opts opts; struct perf_data data; struct perf_session* session; } ;
struct machine {int dummy; } ;
struct TYPE_10__ {struct machine host; } ;
struct perf_session {TYPE_7__ machines; } ;
struct TYPE_8__ {int /*<<< orphan*/  threads; int /*<<< orphan*/  cpus; int /*<<< orphan*/  entries; } ;
struct TYPE_9__ {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int __machine__synthesize_threads (struct machine*,struct perf_tool*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ have_tracepoints (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  machines__process_guests (TYPE_7__*,int /*<<< orphan*/ ,struct perf_tool*) ; 
 int perf_data__fd (struct perf_data*) ; 
 int perf_event__synth_time_conv (int /*<<< orphan*/ ,struct perf_tool*,int /*<<< orphan*/ ,struct machine*) ; 
 int perf_event__synthesize_attrs (struct perf_tool*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int perf_event__synthesize_auxtrace_info (int /*<<< orphan*/ ,struct perf_tool*,struct perf_session*,int /*<<< orphan*/ ) ; 
 int perf_event__synthesize_bpf_events (struct perf_session*,int /*<<< orphan*/ ,struct machine*,struct record_opts*) ; 
 int perf_event__synthesize_cpu_map (struct perf_tool*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int perf_event__synthesize_extra_attr (struct perf_tool*,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int perf_event__synthesize_features (struct perf_tool*,struct perf_session*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event__synthesize_guest_os ; 
 int perf_event__synthesize_kernel_mmap (struct perf_tool*,int /*<<< orphan*/ ,struct machine*) ; 
 int perf_event__synthesize_modules (struct perf_tool*,int /*<<< orphan*/ ,struct machine*) ; 
 int perf_event__synthesize_thread_map2 (struct perf_tool*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int perf_event__synthesize_tracing_data (struct perf_tool*,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__exclude_kernel (TYPE_2__*) ; 
 scalar_t__ perf_guest ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  process_synthesized_event ; 
 int /*<<< orphan*/  record__pick_pc (struct record*) ; 

__attribute__((used)) static int record__synthesize(struct record *rec, bool tail)
{
	struct perf_session *session = rec->session;
	struct machine *machine = &session->machines.host;
	struct perf_data *data = &rec->data;
	struct record_opts *opts = &rec->opts;
	struct perf_tool *tool = &rec->tool;
	int fd = perf_data__fd(data);
	int err = 0;

	if (rec->opts.tail_synthesize != tail)
		return 0;

	if (data->is_pipe) {
		/*
		 * We need to synthesize events first, because some
		 * features works on top of them (on report side).
		 */
		err = perf_event__synthesize_attrs(tool, rec->evlist,
						   process_synthesized_event);
		if (err < 0) {
			pr_err("Couldn't synthesize attrs.\n");
			goto out;
		}

		err = perf_event__synthesize_features(tool, session, rec->evlist,
						      process_synthesized_event);
		if (err < 0) {
			pr_err("Couldn't synthesize features.\n");
			return err;
		}

		if (have_tracepoints(&rec->evlist->core.entries)) {
			/*
			 * FIXME err <= 0 here actually means that
			 * there were no tracepoints so its not really
			 * an error, just that we don't need to
			 * synthesize anything.  We really have to
			 * return this more properly and also
			 * propagate errors that now are calling die()
			 */
			err = perf_event__synthesize_tracing_data(tool,	fd, rec->evlist,
								  process_synthesized_event);
			if (err <= 0) {
				pr_err("Couldn't record tracing data.\n");
				goto out;
			}
			rec->bytes_written += err;
		}
	}

	err = perf_event__synth_time_conv(record__pick_pc(rec), tool,
					  process_synthesized_event, machine);
	if (err)
		goto out;

	if (rec->opts.full_auxtrace) {
		err = perf_event__synthesize_auxtrace_info(rec->itr, tool,
					session, process_synthesized_event);
		if (err)
			goto out;
	}

	if (!perf_evlist__exclude_kernel(rec->evlist)) {
		err = perf_event__synthesize_kernel_mmap(tool, process_synthesized_event,
							 machine);
		WARN_ONCE(err < 0, "Couldn't record kernel reference relocation symbol\n"
				   "Symbol resolution may be skewed if relocation was used (e.g. kexec).\n"
				   "Check /proc/kallsyms permission or run as root.\n");

		err = perf_event__synthesize_modules(tool, process_synthesized_event,
						     machine);
		WARN_ONCE(err < 0, "Couldn't record kernel module information.\n"
				   "Symbol resolution may be skewed if relocation was used (e.g. kexec).\n"
				   "Check /proc/modules permission or run as root.\n");
	}

	if (perf_guest) {
		machines__process_guests(&session->machines,
					 perf_event__synthesize_guest_os, tool);
	}

	err = perf_event__synthesize_extra_attr(&rec->tool,
						rec->evlist,
						process_synthesized_event,
						data->is_pipe);
	if (err)
		goto out;

	err = perf_event__synthesize_thread_map2(&rec->tool, rec->evlist->core.threads,
						 process_synthesized_event,
						NULL);
	if (err < 0) {
		pr_err("Couldn't synthesize thread map.\n");
		return err;
	}

	err = perf_event__synthesize_cpu_map(&rec->tool, rec->evlist->core.cpus,
					     process_synthesized_event, NULL);
	if (err < 0) {
		pr_err("Couldn't synthesize cpu map.\n");
		return err;
	}

	err = perf_event__synthesize_bpf_events(session, process_synthesized_event,
						machine, opts);
	if (err < 0)
		pr_warning("Couldn't synthesize bpf events.\n");

	err = __machine__synthesize_threads(machine, tool, &opts->target, rec->evlist->core.threads,
					    process_synthesized_event, opts->sample_address,
					    1);
out:
	return err;
}