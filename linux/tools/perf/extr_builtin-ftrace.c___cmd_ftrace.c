#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pollfd {int events; int fd; int revents; } ;
struct perf_ftrace {char* tracer; int /*<<< orphan*/  evlist; int /*<<< orphan*/  target; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int POLLIN ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ done ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftrace__workload_exec_failed_signal ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 char* get_tracing_file (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_cap__capable (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_evlist__prepare_workload (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__start_workload (int /*<<< orphan*/ ) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  put_tracing_file (char*) ; 
 int read (int,char*,int) ; 
 scalar_t__ reset_tracing_files (struct perf_ftrace*) ; 
 scalar_t__ set_tracing_cpu (struct perf_ftrace*) ; 
 scalar_t__ set_tracing_depth (struct perf_ftrace*) ; 
 scalar_t__ set_tracing_filters (struct perf_ftrace*) ; 
 scalar_t__ set_tracing_pid (struct perf_ftrace*) ; 
 int /*<<< orphan*/  setup_pager () ; 
 int /*<<< orphan*/  sig_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ write_tracing_file (char*,char*) ; 

__attribute__((used)) static int __cmd_ftrace(struct perf_ftrace *ftrace, int argc, const char **argv)
{
	char *trace_file;
	int trace_fd;
	char buf[4096];
	struct pollfd pollfd = {
		.events = POLLIN,
	};

	if (!perf_cap__capable(CAP_SYS_ADMIN)) {
		pr_err("ftrace only works for %s!\n",
#ifdef HAVE_LIBCAP_SUPPORT
		"users with the SYS_ADMIN capability"
#else
		"root"
#endif
		);
		return -1;
	}

	signal(SIGINT, sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGCHLD, sig_handler);
	signal(SIGPIPE, sig_handler);

	if (reset_tracing_files(ftrace) < 0) {
		pr_err("failed to reset ftrace\n");
		goto out;
	}

	/* reset ftrace buffer */
	if (write_tracing_file("trace", "0") < 0)
		goto out;

	if (argc && perf_evlist__prepare_workload(ftrace->evlist,
				&ftrace->target, argv, false,
				ftrace__workload_exec_failed_signal) < 0) {
		goto out;
	}

	if (set_tracing_pid(ftrace) < 0) {
		pr_err("failed to set ftrace pid\n");
		goto out_reset;
	}

	if (set_tracing_cpu(ftrace) < 0) {
		pr_err("failed to set tracing cpumask\n");
		goto out_reset;
	}

	if (set_tracing_filters(ftrace) < 0) {
		pr_err("failed to set tracing filters\n");
		goto out_reset;
	}

	if (set_tracing_depth(ftrace) < 0) {
		pr_err("failed to set graph depth\n");
		goto out_reset;
	}

	if (write_tracing_file("current_tracer", ftrace->tracer) < 0) {
		pr_err("failed to set current_tracer to %s\n", ftrace->tracer);
		goto out_reset;
	}

	setup_pager();

	trace_file = get_tracing_file("trace_pipe");
	if (!trace_file) {
		pr_err("failed to open trace_pipe\n");
		goto out_reset;
	}

	trace_fd = open(trace_file, O_RDONLY);

	put_tracing_file(trace_file);

	if (trace_fd < 0) {
		pr_err("failed to open trace_pipe\n");
		goto out_reset;
	}

	fcntl(trace_fd, F_SETFL, O_NONBLOCK);
	pollfd.fd = trace_fd;

	if (write_tracing_file("tracing_on", "1") < 0) {
		pr_err("can't enable tracing\n");
		goto out_close_fd;
	}

	perf_evlist__start_workload(ftrace->evlist);

	while (!done) {
		if (poll(&pollfd, 1, -1) < 0)
			break;

		if (pollfd.revents & POLLIN) {
			int n = read(trace_fd, buf, sizeof(buf));
			if (n < 0)
				break;
			if (fwrite(buf, n, 1, stdout) != 1)
				break;
		}
	}

	write_tracing_file("tracing_on", "0");

	/* read remaining buffer contents */
	while (true) {
		int n = read(trace_fd, buf, sizeof(buf));
		if (n <= 0)
			break;
		if (fwrite(buf, n, 1, stdout) != 1)
			break;
	}

out_close_fd:
	close(trace_fd);
out_reset:
	reset_tracing_files(ftrace);
out:
	return done ? 0 : -1;
}