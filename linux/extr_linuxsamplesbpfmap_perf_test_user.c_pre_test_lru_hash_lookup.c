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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_NOEXIST ; 
 int bpf_map_update_elem (int,scalar_t__*,long*,int /*<<< orphan*/ ) ; 
 size_t lru_hash_lookup_idx ; 
 scalar_t__ lru_hash_lookup_test_entries ; 
 int* map_fd ; 
 scalar_t__ num_map_entries ; 

__attribute__((used)) static int pre_test_lru_hash_lookup(int tasks)
{
	int fd = map_fd[lru_hash_lookup_idx];
	uint32_t key;
	long val = 1;
	int ret;

	if (num_map_entries > lru_hash_lookup_test_entries)
		lru_hash_lookup_test_entries = num_map_entries;

	/* Populate the lru_hash_map for LRU_HASH_LOOKUP perf test.
	 *
	 * It is fine that the user requests for a map with
	 * num_map_entries < 32 and some of the later lru hash lookup
	 * may return not found.  For LRU map, we are not interested
	 * in such small map performance.
	 */
	for (key = 0; key < lru_hash_lookup_test_entries; key++) {
		ret = bpf_map_update_elem(fd, &key, &val, BPF_NOEXIST);
		if (ret)
			return ret;
	}

	return 0;
}