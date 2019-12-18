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
 scalar_t__ atoi (char*) ; 
 char* bpf_log_buf ; 
 scalar_t__ load_bpf_file (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  run_perf_test (int,int) ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  unload_progs () ; 

int main(int argc, char **argv)
{
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	char filename[256];
	int num_cpu = 8;
	int test_flags = ~0;

	setrlimit(RLIMIT_MEMLOCK, &r);

	if (argc > 1)
		test_flags = atoi(argv[1]) ? : test_flags;
	if (argc > 2)
		num_cpu = atoi(argv[2]) ? : num_cpu;

	if (test_flags & 0x3) {
		printf("BASE\n");
		run_perf_test(num_cpu, test_flags);
	}

	if (test_flags & 0xC) {
		snprintf(filename, sizeof(filename),
			 "%s_kprobe_kern.o", argv[0]);
		if (load_bpf_file(filename)) {
			printf("%s", bpf_log_buf);
			return 1;
		}
		printf("w/KPROBE\n");
		run_perf_test(num_cpu, test_flags >> 2);
		unload_progs();
	}

	if (test_flags & 0x30) {
		snprintf(filename, sizeof(filename),
			 "%s_tp_kern.o", argv[0]);
		if (load_bpf_file(filename)) {
			printf("%s", bpf_log_buf);
			return 1;
		}
		printf("w/TRACEPOINT\n");
		run_perf_test(num_cpu, test_flags >> 4);
		unload_progs();
	}

	if (test_flags & 0xC0) {
		snprintf(filename, sizeof(filename),
			 "%s_raw_tp_kern.o", argv[0]);
		if (load_bpf_file(filename)) {
			printf("%s", bpf_log_buf);
			return 1;
		}
		printf("w/RAW_TRACEPOINT\n");
		run_perf_test(num_cpu, test_flags >> 6);
		unload_progs();
	}

	return 0;
}