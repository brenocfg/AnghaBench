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
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 char* bpf_log_buf ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ load_bpf_file (char*) ; 
 scalar_t__ perf_event_mmap (int /*<<< orphan*/ ) ; 
 int perf_event_poller (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_fd ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  print_bpf_output ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  test_bpf_perf_event () ; 
 int /*<<< orphan*/  time_get_ns () ; 

int main(int argc, char **argv)
{
	char filename[256];
	FILE *f;
	int ret;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 1;
	}

	test_bpf_perf_event();

	if (perf_event_mmap(pmu_fd) < 0)
		return 1;

	f = popen("taskset 1 dd if=/dev/zero of=/dev/null", "r");
	(void) f;

	start_time = time_get_ns();
	ret = perf_event_poller(pmu_fd, print_bpf_output);
	kill(0, SIGINT);
	return ret;
}