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
typedef  int __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 int SLOTS ; 
 int /*<<< orphan*/  bpf_map_lookup_elem (int,int*,long*) ; 
 unsigned int bpf_num_possible_cpus () ; 
 int /*<<< orphan*/  clear_stats (int) ; 
 char** color ; 
 scalar_t__ full_range ; 
 char* nocolor ; 
 int num_colors ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** sym ; 
 scalar_t__ text_only ; 

__attribute__((used)) static void print_hist(int fd)
{
	unsigned int nr_cpus = bpf_num_possible_cpus();
	__u64 total_events = 0;
	long values[nr_cpus];
	__u64 max_cnt = 0;
	__u64 cnt[SLOTS];
	__u64 value;
	__u32 key;
	int i;

	for (key = 0; key < SLOTS; key++) {
		bpf_map_lookup_elem(fd, &key, values);
		value = 0;
		for (i = 0; i < nr_cpus; i++)
			value += values[i];
		cnt[key] = value;
		total_events += value;
		if (value > max_cnt)
			max_cnt = value;
	}
	clear_stats(fd);
	for (key = full_range ? 0 : 29; key < SLOTS; key++) {
		int c = num_colors * cnt[key] / (max_cnt + 1);

		if (text_only)
			printf("%s", sym[c]);
		else
			printf("%s %s", color[c], nocolor);
	}
	printf(" # %lld\n", total_events);
}