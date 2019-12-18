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
typedef  int /*<<< orphan*/  val ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_EXIST ; 
 int BPF_F_NO_PREALLOC ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_QUEUE ; 
 scalar_t__ E2BIG ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int const,int) ; 
 int bpf_map_delete_elem (int,int /*<<< orphan*/ *) ; 
 int bpf_map_get_next_key (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bpf_map_lookup_and_delete_elem (int,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ bpf_map_lookup_elem (int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int bpf_map_update_elem (int,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int map_flags ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ rand () ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static void test_queuemap(unsigned int task, void *data)
{
	const int MAP_SIZE = 32;
	__u32 vals[MAP_SIZE + MAP_SIZE/2], val;
	int fd, i;

	/* Fill test values to be used */
	for (i = 0; i < MAP_SIZE + MAP_SIZE/2; i++)
		vals[i] = rand();

	/* Invalid key size */
	fd = bpf_create_map(BPF_MAP_TYPE_QUEUE, 4, sizeof(val), MAP_SIZE,
			    map_flags);
	assert(fd < 0 && errno == EINVAL);

	fd = bpf_create_map(BPF_MAP_TYPE_QUEUE, 0, sizeof(val), MAP_SIZE,
			    map_flags);
	/* Queue map does not support BPF_F_NO_PREALLOC */
	if (map_flags & BPF_F_NO_PREALLOC) {
		assert(fd < 0 && errno == EINVAL);
		return;
	}
	if (fd < 0) {
		printf("Failed to create queuemap '%s'!\n", strerror(errno));
		exit(1);
	}

	/* Push MAP_SIZE elements */
	for (i = 0; i < MAP_SIZE; i++)
		assert(bpf_map_update_elem(fd, NULL, &vals[i], 0) == 0);

	/* Check that element cannot be pushed due to max_entries limit */
	assert(bpf_map_update_elem(fd, NULL, &val, 0) == -1 &&
	       errno == E2BIG);

	/* Peek element */
	assert(bpf_map_lookup_elem(fd, NULL, &val) == 0 && val == vals[0]);

	/* Replace half elements */
	for (i = MAP_SIZE; i < MAP_SIZE + MAP_SIZE/2; i++)
		assert(bpf_map_update_elem(fd, NULL, &vals[i], BPF_EXIST) == 0);

	/* Pop all elements */
	for (i = MAP_SIZE/2; i < MAP_SIZE + MAP_SIZE/2; i++)
		assert(bpf_map_lookup_and_delete_elem(fd, NULL, &val) == 0 &&
		       val == vals[i]);

	/* Check that there are not elements left */
	assert(bpf_map_lookup_and_delete_elem(fd, NULL, &val) == -1 &&
	       errno == ENOENT);

	/* Check that non supported functions set errno to EINVAL */
	assert(bpf_map_delete_elem(fd, NULL) == -1 && errno == EINVAL);
	assert(bpf_map_get_next_key(fd, NULL, NULL) == -1 && errno == EINVAL);

	close(fd);
}