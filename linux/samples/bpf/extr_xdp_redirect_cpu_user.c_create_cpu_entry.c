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
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAIL_BPF ; 
 int bpf_map_lookup_elem (int /*<<< orphan*/ ,int*,int*) ; 
 int bpf_map_update_elem (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_map_fd ; 
 int /*<<< orphan*/  cpus_available_map_fd ; 
 int /*<<< orphan*/  cpus_count_map_fd ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int create_cpu_entry(__u32 cpu, __u32 queue_size,
			    __u32 avail_idx, bool new)
{
	__u32 curr_cpus_count = 0;
	__u32 key = 0;
	int ret;

	/* Add a CPU entry to cpumap, as this allocate a cpu entry in
	 * the kernel for the cpu.
	 */
	ret = bpf_map_update_elem(cpu_map_fd, &cpu, &queue_size, 0);
	if (ret) {
		fprintf(stderr, "Create CPU entry failed (err:%d)\n", ret);
		exit(EXIT_FAIL_BPF);
	}

	/* Inform bpf_prog's that a new CPU is available to select
	 * from via some control maps.
	 */
	ret = bpf_map_update_elem(cpus_available_map_fd, &avail_idx, &cpu, 0);
	if (ret) {
		fprintf(stderr, "Add to avail CPUs failed\n");
		exit(EXIT_FAIL_BPF);
	}

	/* When not replacing/updating existing entry, bump the count */
	ret = bpf_map_lookup_elem(cpus_count_map_fd, &key, &curr_cpus_count);
	if (ret) {
		fprintf(stderr, "Failed reading curr cpus_count\n");
		exit(EXIT_FAIL_BPF);
	}
	if (new) {
		curr_cpus_count++;
		ret = bpf_map_update_elem(cpus_count_map_fd, &key,
					  &curr_cpus_count, 0);
		if (ret) {
			fprintf(stderr, "Failed write curr cpus_count\n");
			exit(EXIT_FAIL_BPF);
		}
	}
	/* map_fd[7] = cpus_iterator */
	printf("%s CPU:%u as idx:%u queue_size:%d (total cpus_count:%u)\n",
	       new ? "Add-new":"Replace", cpu, avail_idx,
	       queue_size, curr_cpus_count);

	return 0;
}