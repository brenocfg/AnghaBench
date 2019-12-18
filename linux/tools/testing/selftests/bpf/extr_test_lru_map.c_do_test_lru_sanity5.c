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
 int /*<<< orphan*/  BPF_NOEXIST ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_map_lookup_elem (int,unsigned long long*,unsigned long long*) ; 
 int /*<<< orphan*/  bpf_map_lookup_elem_with_ref_bit (int,unsigned long long,unsigned long long*) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int,unsigned long long*,unsigned long long*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int nr_cpus ; 

__attribute__((used)) static void do_test_lru_sanity5(unsigned long long last_key, int map_fd)
{
	unsigned long long key, value[nr_cpus];

	/* Ensure the last key inserted by previous CPU can be found */
	assert(!bpf_map_lookup_elem_with_ref_bit(map_fd, last_key, value));
	value[0] = 1234;

	key = last_key + 1;
	assert(!bpf_map_update_elem(map_fd, &key, value, BPF_NOEXIST));
	assert(!bpf_map_lookup_elem_with_ref_bit(map_fd, key, value));

	/* Cannot find the last key because it was removed by LRU */
	assert(bpf_map_lookup_elem(map_fd, &last_key, value) == -1 &&
	       errno == ENOENT);
}