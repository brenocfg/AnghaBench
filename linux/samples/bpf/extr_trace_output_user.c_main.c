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
struct perf_buffer_opts {int /*<<< orphan*/  sample_cb; } ;
struct perf_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ MAX_CNT ; 
 int /*<<< orphan*/  SIGINT ; 
 char* bpf_log_buf ; 
 scalar_t__ cnt ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int libbpf_get_error (struct perf_buffer*) ; 
 scalar_t__ load_bpf_file (char*) ; 
 int /*<<< orphan*/ * map_fd ; 
 struct perf_buffer* perf_buffer__new (int /*<<< orphan*/ ,int,struct perf_buffer_opts*) ; 
 int perf_buffer__poll (struct perf_buffer*,int) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  print_bpf_output ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  time_get_ns () ; 

int main(int argc, char **argv)
{
	struct perf_buffer_opts pb_opts = {};
	struct perf_buffer *pb;
	char filename[256];
	FILE *f;
	int ret;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 1;
	}

	pb_opts.sample_cb = print_bpf_output;
	pb = perf_buffer__new(map_fd[0], 8, &pb_opts);
	ret = libbpf_get_error(pb);
	if (ret) {
		printf("failed to setup perf_buffer: %d\n", ret);
		return 1;
	}

	f = popen("taskset 1 dd if=/dev/zero of=/dev/null", "r");
	(void) f;

	start_time = time_get_ns();
	while ((ret = perf_buffer__poll(pb, 1000)) >= 0 && cnt < MAX_CNT) {
	}
	kill(0, SIGINT);
	return ret;
}