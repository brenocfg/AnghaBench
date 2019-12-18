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
typedef  int /*<<< orphan*/  map_types ;
typedef  int /*<<< orphan*/  map_flags ;

/* Variables and functions */
 int BPF_F_NO_COMMON_LRU ; 
 int BPF_MAP_TYPE_LRU_HASH ; 
 int BPF_MAP_TYPE_LRU_PERCPU_HASH ; 
 unsigned int LOCAL_FREE_TARGET ; 
 unsigned int PERCPU_FREE_TARGET ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_num_possible_cpus () ; 
 int nr_cpus ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  test_lru_sanity0 (int,int) ; 
 int /*<<< orphan*/  test_lru_sanity1 (int,int,unsigned int) ; 
 int /*<<< orphan*/  test_lru_sanity2 (int,int,unsigned int) ; 
 int /*<<< orphan*/  test_lru_sanity3 (int,int,unsigned int) ; 
 int /*<<< orphan*/  test_lru_sanity4 (int,int,unsigned int) ; 
 int /*<<< orphan*/  test_lru_sanity5 (int,int) ; 
 int /*<<< orphan*/  test_lru_sanity6 (int,int,unsigned int) ; 
 int /*<<< orphan*/  test_lru_sanity7 (int,int) ; 
 int /*<<< orphan*/  test_lru_sanity8 (int,int) ; 

int main(int argc, char **argv)
{
	int map_types[] = {BPF_MAP_TYPE_LRU_HASH,
			     BPF_MAP_TYPE_LRU_PERCPU_HASH};
	int map_flags[] = {0, BPF_F_NO_COMMON_LRU};
	int t, f;

	setbuf(stdout, NULL);

	nr_cpus = bpf_num_possible_cpus();
	assert(nr_cpus != -1);
	printf("nr_cpus:%d\n\n", nr_cpus);

	for (f = 0; f < sizeof(map_flags) / sizeof(*map_flags); f++) {
		unsigned int tgt_free = (map_flags[f] & BPF_F_NO_COMMON_LRU) ?
			PERCPU_FREE_TARGET : LOCAL_FREE_TARGET;

		for (t = 0; t < sizeof(map_types) / sizeof(*map_types); t++) {
			test_lru_sanity0(map_types[t], map_flags[f]);
			test_lru_sanity1(map_types[t], map_flags[f], tgt_free);
			test_lru_sanity2(map_types[t], map_flags[f], tgt_free);
			test_lru_sanity3(map_types[t], map_flags[f], tgt_free);
			test_lru_sanity4(map_types[t], map_flags[f], tgt_free);
			test_lru_sanity5(map_types[t], map_flags[f]);
			test_lru_sanity6(map_types[t], map_flags[f], tgt_free);
			test_lru_sanity7(map_types[t], map_flags[f]);
			test_lru_sanity8(map_types[t], map_flags[f]);

			printf("\n");
		}
	}

	return 0;
}