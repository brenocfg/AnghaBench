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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_TYPE_HASH ; 
 int /*<<< orphan*/  BPF_NOEXIST ; 
 int /*<<< orphan*/  CHECK (int,char*,char*,int /*<<< orphan*/ ,...) ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int bpf_map_update_elem (int,long long*,long long*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  map_flags ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int helper_fill_hashmap(int max_entries)
{
	int i, fd, ret;
	long long key, value;

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, sizeof(key), sizeof(value),
			    max_entries, map_flags);
	CHECK(fd < 0,
	      "failed to create hashmap",
	      "err: %s, flags: 0x%x\n", strerror(errno), map_flags);

	for (i = 0; i < max_entries; i++) {
		key = i; value = key;
		ret = bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST);
		CHECK(ret != 0,
		      "can't update hashmap",
		      "err: %s\n", strerror(ret));
	}

	return fd;
}