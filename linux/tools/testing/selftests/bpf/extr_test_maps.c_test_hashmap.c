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
 int BPF_ANY ; 
 int BPF_EXIST ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_HASH ; 
 int BPF_NOEXIST ; 
 scalar_t__ E2BIG ; 
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int bpf_map_delete_elem (int,long long*) ; 
 int bpf_map_get_next_key (int,long long*,long long*) ; 
 int bpf_map_lookup_elem (int,long long*,long long*) ; 
 int bpf_map_update_elem (int,long long*,long long*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  map_flags ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static void test_hashmap(unsigned int task, void *data)
{
	long long key, next_key, first_key, value;
	int fd;

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, sizeof(key), sizeof(value),
			    2, map_flags);
	if (fd < 0) {
		printf("Failed to create hashmap '%s'!\n", strerror(errno));
		exit(1);
	}

	key = 1;
	value = 1234;
	/* Insert key=1 element. */
	assert(bpf_map_update_elem(fd, &key, &value, BPF_ANY) == 0);

	value = 0;
	/* BPF_NOEXIST means add new element if it doesn't exist. */
	assert(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       /* key=1 already exists. */
	       errno == EEXIST);

	/* -1 is an invalid flag. */
	assert(bpf_map_update_elem(fd, &key, &value, -1) == -1 &&
	       errno == EINVAL);

	/* Check that key=1 can be found. */
	assert(bpf_map_lookup_elem(fd, &key, &value) == 0 && value == 1234);

	key = 2;
	/* Check that key=2 is not found. */
	assert(bpf_map_lookup_elem(fd, &key, &value) == -1 && errno == ENOENT);

	/* BPF_EXIST means update existing element. */
	assert(bpf_map_update_elem(fd, &key, &value, BPF_EXIST) == -1 &&
	       /* key=2 is not there. */
	       errno == ENOENT);

	/* Insert key=2 element. */
	assert(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == 0);

	/* key=1 and key=2 were inserted, check that key=0 cannot be
	 * inserted due to max_entries limit.
	 */
	key = 0;
	assert(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       errno == E2BIG);

	/* Update existing element, though the map is full. */
	key = 1;
	assert(bpf_map_update_elem(fd, &key, &value, BPF_EXIST) == 0);
	key = 2;
	assert(bpf_map_update_elem(fd, &key, &value, BPF_ANY) == 0);
	key = 3;
	assert(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       errno == E2BIG);

	/* Check that key = 0 doesn't exist. */
	key = 0;
	assert(bpf_map_delete_elem(fd, &key) == -1 && errno == ENOENT);

	/* Iterate over two elements. */
	assert(bpf_map_get_next_key(fd, NULL, &first_key) == 0 &&
	       (first_key == 1 || first_key == 2));
	assert(bpf_map_get_next_key(fd, &key, &next_key) == 0 &&
	       (next_key == first_key));
	assert(bpf_map_get_next_key(fd, &next_key, &next_key) == 0 &&
	       (next_key == 1 || next_key == 2) &&
	       (next_key != first_key));
	assert(bpf_map_get_next_key(fd, &next_key, &next_key) == -1 &&
	       errno == ENOENT);

	/* Delete both elements. */
	key = 1;
	assert(bpf_map_delete_elem(fd, &key) == 0);
	key = 2;
	assert(bpf_map_delete_elem(fd, &key) == 0);
	assert(bpf_map_delete_elem(fd, &key) == -1 && errno == ENOENT);

	key = 0;
	/* Check that map is empty. */
	assert(bpf_map_get_next_key(fd, NULL, &next_key) == -1 &&
	       errno == ENOENT);
	assert(bpf_map_get_next_key(fd, &key, &next_key) == -1 &&
	       errno == ENOENT);

	close(fd);
}