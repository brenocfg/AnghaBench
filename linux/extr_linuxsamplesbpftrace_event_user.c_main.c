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
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 char* bpf_log_buf ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  int_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ load_bpf_file (char*) ; 
 scalar_t__ load_kallsyms () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_trace_pipe () ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  test_bpf_perf_event () ; 

int main(int argc, char **argv)
{
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	char filename[256];

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	setrlimit(RLIMIT_MEMLOCK, &r);

	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);

	if (load_kallsyms()) {
		printf("failed to process /proc/kallsyms\n");
		return 1;
	}

	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 2;
	}

	if (fork() == 0) {
		read_trace_pipe();
		return 0;
	}
	test_bpf_perf_event();
	int_exit(0);
	return 0;
}