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
 int DO_DELETE ; 
 int DO_UPDATE ; 
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 int MAP_SIZE ; 
 int /*<<< orphan*/  TASKS ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int bpf_map_get_next_key (int,int*,int*) ; 
 scalar_t__ bpf_map_lookup_elem (int,int*,int*) ; 
 int bpf_map_update_elem (int,int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  map_flags ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  run_parallel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  test_update_delete ; 

__attribute__((used)) static void test_map_parallel(void)
{
	int i, fd, key = 0, value = 0;
	int data[2];

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, sizeof(key), sizeof(value),
			    MAP_SIZE, map_flags);
	if (fd < 0) {
		printf("Failed to create map for parallel test '%s'!\n",
		       strerror(errno));
		exit(1);
	}

	/* Use the same fd in children to add elements to this map:
	 * child_0 adds key=0, key=1024, key=2048, ...
	 * child_1 adds key=1, key=1025, key=2049, ...
	 * child_1023 adds key=1023, ...
	 */
	data[0] = fd;
	data[1] = DO_UPDATE;
	run_parallel(TASKS, test_update_delete, data);

	/* Check that key=0 is already there. */
	assert(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       errno == EEXIST);

	/* Check that all elements were inserted. */
	assert(bpf_map_get_next_key(fd, NULL, &key) == 0);
	key = -1;
	for (i = 0; i < MAP_SIZE; i++)
		assert(bpf_map_get_next_key(fd, &key, &key) == 0);
	assert(bpf_map_get_next_key(fd, &key, &key) == -1 && errno == ENOENT);

	/* Another check for all elements */
	for (i = 0; i < MAP_SIZE; i++) {
		key = MAP_SIZE - i - 1;

		assert(bpf_map_lookup_elem(fd, &key, &value) == 0 &&
		       value == key);
	}

	/* Now let's delete all elemenets in parallel. */
	data[1] = DO_DELETE;
	run_parallel(TASKS, test_update_delete, data);

	/* Nothing should be left. */
	key = -1;
	assert(bpf_map_get_next_key(fd, NULL, &key) == -1 && errno == ENOENT);
	assert(bpf_map_get_next_key(fd, &key, &key) == -1 && errno == ENOENT);
}