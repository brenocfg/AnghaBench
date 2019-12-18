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
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  BPF_EXIST ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_ARRAY ; 
 int /*<<< orphan*/  BPF_NOEXIST ; 
 scalar_t__ E2BIG ; 
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int bpf_map_delete_elem (int,int*) ; 
 int bpf_map_get_next_key (int,int*,int*) ; 
 int bpf_map_lookup_elem (int,int*,long long*) ; 
 int bpf_map_update_elem (int,int*,long long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static void test_arraymap(unsigned int task, void *data)
{
	int key, next_key, fd;
	long long value;

	fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, sizeof(key), sizeof(value),
			    2, 0);
	if (fd < 0) {
		printf("Failed to create arraymap '%s'!\n", strerror(errno));
		exit(1);
	}

	key = 1;
	value = 1234;
	/* Insert key=1 element. */
	assert(bpf_map_update_elem(fd, &key, &value, BPF_ANY) == 0);

	value = 0;
	assert(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       errno == EEXIST);

	/* Check that key=1 can be found. */
	assert(bpf_map_lookup_elem(fd, &key, &value) == 0 && value == 1234);

	key = 0;
	/* Check that key=0 is also found and zero initialized. */
	assert(bpf_map_lookup_elem(fd, &key, &value) == 0 && value == 0);

	/* key=0 and key=1 were inserted, check that key=2 cannot be inserted
	 * due to max_entries limit.
	 */
	key = 2;
	assert(bpf_map_update_elem(fd, &key, &value, BPF_EXIST) == -1 &&
	       errno == E2BIG);

	/* Check that key = 2 doesn't exist. */
	assert(bpf_map_lookup_elem(fd, &key, &value) == -1 && errno == ENOENT);

	/* Iterate over two elements. */
	assert(bpf_map_get_next_key(fd, NULL, &next_key) == 0 &&
	       next_key == 0);
	assert(bpf_map_get_next_key(fd, &key, &next_key) == 0 &&
	       next_key == 0);
	assert(bpf_map_get_next_key(fd, &next_key, &next_key) == 0 &&
	       next_key == 1);
	assert(bpf_map_get_next_key(fd, &next_key, &next_key) == -1 &&
	       errno == ENOENT);

	/* Delete shouldn't succeed. */
	key = 1;
	assert(bpf_map_delete_elem(fd, &key) == -1 && errno == EINVAL);

	close(fd);
}