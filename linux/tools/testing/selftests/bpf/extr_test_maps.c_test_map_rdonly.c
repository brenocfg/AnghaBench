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
 int BPF_F_RDONLY ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_HASH ; 
 scalar_t__ ENOENT ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  MAP_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int bpf_map_get_next_key (int,int*,int*) ; 
 int bpf_map_lookup_elem (int,int*,int*) ; 
 int bpf_map_update_elem (int,int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int map_flags ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static void test_map_rdonly(void)
{
	int fd, key = 0, value = 0;

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, sizeof(key), sizeof(value),
			    MAP_SIZE, map_flags | BPF_F_RDONLY);
	if (fd < 0) {
		printf("Failed to create map for read only test '%s'!\n",
		       strerror(errno));
		exit(1);
	}

	key = 1;
	value = 1234;
	/* Insert key=1 element. */
	assert(bpf_map_update_elem(fd, &key, &value, BPF_ANY) == -1 &&
	       errno == EPERM);

	/* Check that key=2 is not found. */
	assert(bpf_map_lookup_elem(fd, &key, &value) == -1 && errno == ENOENT);
	assert(bpf_map_get_next_key(fd, &key, &value) == -1 && errno == ENOENT);
}