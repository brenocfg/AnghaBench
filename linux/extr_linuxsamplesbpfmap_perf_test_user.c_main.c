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
 void* atoi (char*) ; 
 char* bpf_log_buf ; 
 int /*<<< orphan*/  fill_lpm_trie () ; 
 int /*<<< orphan*/  fixup_map ; 
 scalar_t__ load_bpf_file_fixup_map (char*,int /*<<< orphan*/ ) ; 
 void* max_cnt ; 
 void* num_map_entries ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  run_perf_test (int) ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  test_flags ; 

int main(int argc, char **argv)
{
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	char filename[256];
	int num_cpu = 8;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	setrlimit(RLIMIT_MEMLOCK, &r);

	if (argc > 1)
		test_flags = atoi(argv[1]) ? : test_flags;

	if (argc > 2)
		num_cpu = atoi(argv[2]) ? : num_cpu;

	if (argc > 3)
		num_map_entries = atoi(argv[3]);

	if (argc > 4)
		max_cnt = atoi(argv[4]);

	if (load_bpf_file_fixup_map(filename, fixup_map)) {
		printf("%s", bpf_log_buf);
		return 1;
	}

	fill_lpm_trie();

	run_perf_test(num_cpu);

	return 0;
}