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
 int /*<<< orphan*/  BPF_EXIST ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bpf_map_get_next_key (int,long long*,long long*) ; 
 scalar_t__ bpf_map_lookup_elem (int,long long*,long long*) ; 
 scalar_t__ bpf_map_update_elem (int,long long*,long long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int helper_fill_hashmap (int) ; 

__attribute__((used)) static void test_hashmap_walk(unsigned int task, void *data)
{
	int fd, i, max_entries = 1000;
	long long key, value, next_key;
	bool next_key_valid = true;

	fd = helper_fill_hashmap(max_entries);

	for (i = 0; bpf_map_get_next_key(fd, !i ? NULL : &key,
					 &next_key) == 0; i++) {
		key = next_key;
		assert(bpf_map_lookup_elem(fd, &key, &value) == 0);
	}

	assert(i == max_entries);

	assert(bpf_map_get_next_key(fd, NULL, &key) == 0);
	for (i = 0; next_key_valid; i++) {
		next_key_valid = bpf_map_get_next_key(fd, &key, &next_key) == 0;
		assert(bpf_map_lookup_elem(fd, &key, &value) == 0);
		value++;
		assert(bpf_map_update_elem(fd, &key, &value, BPF_EXIST) == 0);
		key = next_key;
	}

	assert(i == max_entries);

	for (i = 0; bpf_map_get_next_key(fd, !i ? NULL : &key,
					 &next_key) == 0; i++) {
		key = next_key;
		assert(bpf_map_lookup_elem(fd, &key, &value) == 0);
		assert(value - 1 == key);
	}

	assert(i == max_entries);
	close(fd);
}