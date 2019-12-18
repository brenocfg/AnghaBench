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
 int BPF_F_ZERO_SEED ; 
 int /*<<< orphan*/  CHECK (int,char*,char*,int,...) ; 
 scalar_t__ bpf_map_get_next_key (int,void*,long long*) ; 
 int /*<<< orphan*/  close (int) ; 
 int helper_fill_hashmap (int) ; 
 int map_flags ; 

__attribute__((used)) static void test_hashmap_zero_seed(void)
{
	int i, first, second, old_flags;
	long long key, next_first, next_second;

	old_flags = map_flags;
	map_flags |= BPF_F_ZERO_SEED;

	first = helper_fill_hashmap(3);
	second = helper_fill_hashmap(3);

	for (i = 0; ; i++) {
		void *key_ptr = !i ? NULL : &key;

		if (bpf_map_get_next_key(first, key_ptr, &next_first) != 0)
			break;

		CHECK(bpf_map_get_next_key(second, key_ptr, &next_second) != 0,
		      "next_key for second map must succeed",
		      "key_ptr: %p", key_ptr);
		CHECK(next_first != next_second,
		      "keys must match",
		      "i: %d first: %lld second: %lld\n", i,
		      next_first, next_second);

		key = next_first;
	}

	map_flags = old_flags;
	close(first);
	close(second);
}