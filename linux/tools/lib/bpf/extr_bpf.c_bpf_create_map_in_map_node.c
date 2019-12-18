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
union bpf_attr {int map_type; int key_size; int value_size; int inner_map_fd; int max_entries; int numa_node; int /*<<< orphan*/  map_flags; int /*<<< orphan*/  map_name; } ;
typedef  enum bpf_map_type { ____Placeholder_bpf_map_type } bpf_map_type ;
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_NUMA_NODE ; 
 int /*<<< orphan*/  BPF_MAP_CREATE ; 
 scalar_t__ BPF_OBJ_NAME_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union bpf_attr*,char,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_create_map_in_map_node(enum bpf_map_type map_type, const char *name,
			       int key_size, int inner_map_fd, int max_entries,
			       __u32 map_flags, int node)
{
	union bpf_attr attr;

	memset(&attr, '\0', sizeof(attr));

	attr.map_type = map_type;
	attr.key_size = key_size;
	attr.value_size = 4;
	attr.inner_map_fd = inner_map_fd;
	attr.max_entries = max_entries;
	attr.map_flags = map_flags;
	if (name)
		memcpy(attr.map_name, name,
		       min(strlen(name), BPF_OBJ_NAME_LEN - 1));

	if (node >= 0) {
		attr.map_flags |= BPF_F_NUMA_NODE;
		attr.numa_node = node;
	}

	return sys_bpf(BPF_MAP_CREATE, &attr, sizeof(attr));
}