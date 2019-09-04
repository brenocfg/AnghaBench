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
struct bpf_cgroup_storage_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_TYPE_CGROUP_STORAGE ; 
 int /*<<< orphan*/  TEST_DATA_LEN ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_cgroup_storage(void)
{
	int fd;

	fd = bpf_create_map(BPF_MAP_TYPE_CGROUP_STORAGE,
			    sizeof(struct bpf_cgroup_storage_key),
			    TEST_DATA_LEN, 0, 0);
	if (fd < 0)
		printf("Failed to create array '%s'!\n", strerror(errno));

	return fd;
}