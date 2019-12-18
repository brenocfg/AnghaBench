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
struct pfect_lru {int nr_unique; int total; unsigned int nr_misses; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_NOEXIST ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_map_lookup_elem (unsigned int,unsigned long long*,unsigned long long*) ; 
 scalar_t__ bpf_map_update_elem (unsigned int,unsigned long long*,unsigned long long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (unsigned int) ; 
 int dist_key_counts ; 
 unsigned long long* dist_keys ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pfect_lru_destroy (struct pfect_lru*) ; 
 int /*<<< orphan*/  pfect_lru_init (struct pfect_lru*,unsigned int,int) ; 
 int /*<<< orphan*/  pfect_lru_lookup_or_insert (struct pfect_lru*,unsigned long long) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

__attribute__((used)) static void do_test_lru_dist(int task, void *data)
{
	unsigned int nr_misses = 0;
	struct pfect_lru pfect_lru;
	unsigned long long key, value = 1234;
	unsigned int i;

	unsigned int lru_map_fd = ((unsigned int *)data)[0];
	unsigned int lru_size = ((unsigned int *)data)[1];
	unsigned long long key_offset = task * dist_key_counts;

	pfect_lru_init(&pfect_lru, lru_size, dist_key_counts);

	for (i = 0; i < dist_key_counts; i++) {
		key = dist_keys[i] + key_offset;

		pfect_lru_lookup_or_insert(&pfect_lru, key);

		if (!bpf_map_lookup_elem(lru_map_fd, &key, &value))
			continue;

		if (bpf_map_update_elem(lru_map_fd, &key, &value, BPF_NOEXIST)) {
			printf("bpf_map_update_elem(lru_map_fd, %llu): errno:%d\n",
			       key, errno);
			assert(0);
		}

		nr_misses++;
	}

	printf("    task:%d BPF LRU: nr_unique:%u(/%u) nr_misses:%u(/%u)\n",
	       task, pfect_lru.nr_unique, dist_key_counts, nr_misses,
	       dist_key_counts);
	printf("    task:%d Perfect LRU: nr_unique:%u(/%u) nr_misses:%u(/%u)\n",
	       task, pfect_lru.nr_unique, pfect_lru.total,
	       pfect_lru.nr_misses, pfect_lru.total);

	pfect_lru_destroy(&pfect_lru);
	close(lru_map_fd);
}