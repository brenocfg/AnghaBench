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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bpf_map_get_next_key (int,unsigned long long*,unsigned long long*) ; 
 int bpf_map_lookup_elem (int,unsigned long long*,unsigned long long*) ; 
 unsigned long long errno ; 
 int nr_cpus ; 
 int /*<<< orphan*/  printf (char*,unsigned long long,unsigned long long,unsigned long long) ; 
 unsigned long long strerror (unsigned long long) ; 

__attribute__((used)) static int map_subset(int map0, int map1)
{
	unsigned long long next_key = 0;
	unsigned long long value0[nr_cpus], value1[nr_cpus];
	int ret;

	while (!bpf_map_get_next_key(map1, &next_key, &next_key)) {
		assert(!bpf_map_lookup_elem(map1, &next_key, value1));
		ret = bpf_map_lookup_elem(map0, &next_key, value0);
		if (ret) {
			printf("key:%llu not found from map. %s(%d)\n",
			       next_key, strerror(errno), errno);
			return 0;
		}
		if (value0[0] != value1[0]) {
			printf("key:%llu value0:%llu != value1:%llu\n",
			       next_key, value0[0], value1[0]);
			return 0;
		}
	}
	return 1;
}