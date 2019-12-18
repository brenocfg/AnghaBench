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
typedef  enum bpf_map_type { ____Placeholder_bpf_map_type } bpf_map_type ;

/* Variables and functions */
 int BPF_MAP_TYPE_CGROUP_STORAGE ; 
 int BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE ; 
 int /*<<< orphan*/  TEST_DATA_LEN ; 
 int bpf_create_map (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ skip_unsupported_map (int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_cgroup_storage(bool percpu)
{
	enum bpf_map_type type = percpu ? BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE :
		BPF_MAP_TYPE_CGROUP_STORAGE;
	int fd;

	fd = bpf_create_map(type, sizeof(struct bpf_cgroup_storage_key),
			    TEST_DATA_LEN, 0, 0);
	if (fd < 0) {
		if (skip_unsupported_map(type))
			return -1;
		printf("Failed to create cgroup storage '%s'!\n",
		       strerror(errno));
	}

	return fd;
}