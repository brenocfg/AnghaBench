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
struct timechart {double last_time; double first_time; int /*<<< orphan*/  tool; int /*<<< orphan*/  force; } ;
struct TYPE_2__ {int /*<<< orphan*/  env; } ;
struct perf_session {int /*<<< orphan*/  data; TYPE_1__ header; } ;
struct perf_data {int /*<<< orphan*/  force; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
struct evsel_str_handler {char* member_0; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct perf_session*) ; 
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  PERF_DATA_MODE_READ ; 
 int PTR_ERR (struct perf_session*) ; 
 int /*<<< orphan*/  end_sample_processing (struct timechart*) ; 
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  perf_data__fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_header__process_sections (TYPE_1__*,int /*<<< orphan*/ ,struct timechart*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__has_traces (struct perf_session*,char*) ; 
 struct perf_session* perf_session__new (struct perf_data*,int,int /*<<< orphan*/ *) ; 
 int perf_session__process_events (struct perf_session*) ; 
 scalar_t__ perf_session__set_tracepoints_handlers (struct perf_session*,struct evsel_str_handler const*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,double,char const*) ; 
 int /*<<< orphan*/  process_enter_poll ; 
 int /*<<< orphan*/  process_enter_read ; 
 int /*<<< orphan*/  process_enter_rx ; 
 int /*<<< orphan*/  process_enter_sync ; 
 int /*<<< orphan*/  process_enter_tx ; 
 int /*<<< orphan*/  process_enter_write ; 
 int /*<<< orphan*/  process_exit_poll ; 
 int /*<<< orphan*/  process_exit_read ; 
 int /*<<< orphan*/  process_exit_rx ; 
 int /*<<< orphan*/  process_exit_sync ; 
 int /*<<< orphan*/  process_exit_tx ; 
 int /*<<< orphan*/  process_exit_write ; 
 int /*<<< orphan*/  process_header ; 
 int /*<<< orphan*/  process_sample_cpu_frequency ; 
 int /*<<< orphan*/  process_sample_cpu_idle ; 
 int /*<<< orphan*/  process_sample_power_end ; 
 int /*<<< orphan*/  process_sample_power_frequency ; 
 int /*<<< orphan*/  process_sample_power_start ; 
 int /*<<< orphan*/  process_sample_sched_switch ; 
 int /*<<< orphan*/  process_sample_sched_wakeup ; 
 int /*<<< orphan*/  sort_pids (struct timechart*) ; 
 int /*<<< orphan*/  symbol__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_svg_file (struct timechart*,char const*) ; 

__attribute__((used)) static int __cmd_timechart(struct timechart *tchart, const char *output_name)
{
	const struct evsel_str_handler power_tracepoints[] = {
		{ "power:cpu_idle",		process_sample_cpu_idle },
		{ "power:cpu_frequency",	process_sample_cpu_frequency },
		{ "sched:sched_wakeup",		process_sample_sched_wakeup },
		{ "sched:sched_switch",		process_sample_sched_switch },
#ifdef SUPPORT_OLD_POWER_EVENTS
		{ "power:power_start",		process_sample_power_start },
		{ "power:power_end",		process_sample_power_end },
		{ "power:power_frequency",	process_sample_power_frequency },
#endif

		{ "syscalls:sys_enter_read",		process_enter_read },
		{ "syscalls:sys_enter_pread64",		process_enter_read },
		{ "syscalls:sys_enter_readv",		process_enter_read },
		{ "syscalls:sys_enter_preadv",		process_enter_read },
		{ "syscalls:sys_enter_write",		process_enter_write },
		{ "syscalls:sys_enter_pwrite64",	process_enter_write },
		{ "syscalls:sys_enter_writev",		process_enter_write },
		{ "syscalls:sys_enter_pwritev",		process_enter_write },
		{ "syscalls:sys_enter_sync",		process_enter_sync },
		{ "syscalls:sys_enter_sync_file_range",	process_enter_sync },
		{ "syscalls:sys_enter_fsync",		process_enter_sync },
		{ "syscalls:sys_enter_msync",		process_enter_sync },
		{ "syscalls:sys_enter_recvfrom",	process_enter_rx },
		{ "syscalls:sys_enter_recvmmsg",	process_enter_rx },
		{ "syscalls:sys_enter_recvmsg",		process_enter_rx },
		{ "syscalls:sys_enter_sendto",		process_enter_tx },
		{ "syscalls:sys_enter_sendmsg",		process_enter_tx },
		{ "syscalls:sys_enter_sendmmsg",	process_enter_tx },
		{ "syscalls:sys_enter_epoll_pwait",	process_enter_poll },
		{ "syscalls:sys_enter_epoll_wait",	process_enter_poll },
		{ "syscalls:sys_enter_poll",		process_enter_poll },
		{ "syscalls:sys_enter_ppoll",		process_enter_poll },
		{ "syscalls:sys_enter_pselect6",	process_enter_poll },
		{ "syscalls:sys_enter_select",		process_enter_poll },

		{ "syscalls:sys_exit_read",		process_exit_read },
		{ "syscalls:sys_exit_pread64",		process_exit_read },
		{ "syscalls:sys_exit_readv",		process_exit_read },
		{ "syscalls:sys_exit_preadv",		process_exit_read },
		{ "syscalls:sys_exit_write",		process_exit_write },
		{ "syscalls:sys_exit_pwrite64",		process_exit_write },
		{ "syscalls:sys_exit_writev",		process_exit_write },
		{ "syscalls:sys_exit_pwritev",		process_exit_write },
		{ "syscalls:sys_exit_sync",		process_exit_sync },
		{ "syscalls:sys_exit_sync_file_range",	process_exit_sync },
		{ "syscalls:sys_exit_fsync",		process_exit_sync },
		{ "syscalls:sys_exit_msync",		process_exit_sync },
		{ "syscalls:sys_exit_recvfrom",		process_exit_rx },
		{ "syscalls:sys_exit_recvmmsg",		process_exit_rx },
		{ "syscalls:sys_exit_recvmsg",		process_exit_rx },
		{ "syscalls:sys_exit_sendto",		process_exit_tx },
		{ "syscalls:sys_exit_sendmsg",		process_exit_tx },
		{ "syscalls:sys_exit_sendmmsg",		process_exit_tx },
		{ "syscalls:sys_exit_epoll_pwait",	process_exit_poll },
		{ "syscalls:sys_exit_epoll_wait",	process_exit_poll },
		{ "syscalls:sys_exit_poll",		process_exit_poll },
		{ "syscalls:sys_exit_ppoll",		process_exit_poll },
		{ "syscalls:sys_exit_pselect6",		process_exit_poll },
		{ "syscalls:sys_exit_select",		process_exit_poll },
	};
	struct perf_data data = {
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.force = tchart->force,
	};

	struct perf_session *session = perf_session__new(&data, false,
							 &tchart->tool);
	int ret = -EINVAL;

	if (IS_ERR(session))
		return PTR_ERR(session);

	symbol__init(&session->header.env);

	(void)perf_header__process_sections(&session->header,
					    perf_data__fd(session->data),
					    tchart,
					    process_header);

	if (!perf_session__has_traces(session, "timechart record"))
		goto out_delete;

	if (perf_session__set_tracepoints_handlers(session,
						   power_tracepoints)) {
		pr_err("Initializing session tracepoint handlers failed\n");
		goto out_delete;
	}

	ret = perf_session__process_events(session);
	if (ret)
		goto out_delete;

	end_sample_processing(tchart);

	sort_pids(tchart);

	write_svg_file(tchart, output_name);

	pr_info("Written %2.1f seconds of trace to %s.\n",
		(tchart->last_time - tchart->first_time) / (double)NSEC_PER_SEC, output_name);
out_delete:
	perf_session__delete(session);
	return ret;
}