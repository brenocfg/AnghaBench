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
union bpf_attr {int /*<<< orphan*/  inner_map_fd; int /*<<< orphan*/  map_ifindex; int /*<<< orphan*/  btf_value_type_id; int /*<<< orphan*/  btf_key_type_id; int /*<<< orphan*/  btf_fd; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  map_name; int /*<<< orphan*/  map_flags; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map_type; } ;
struct bpf_create_map_attr {int /*<<< orphan*/  inner_map_fd; int /*<<< orphan*/  map_ifindex; int /*<<< orphan*/  btf_value_type_id; int /*<<< orphan*/  btf_key_type_id; int /*<<< orphan*/  btf_fd; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  name; int /*<<< orphan*/  map_flags; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map_type; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_CREATE ; 
 scalar_t__ BPF_OBJ_NAME_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union bpf_attr*,char,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_create_map_xattr(const struct bpf_create_map_attr *create_attr)
{
	union bpf_attr attr;

	memset(&attr, '\0', sizeof(attr));

	attr.map_type = create_attr->map_type;
	attr.key_size = create_attr->key_size;
	attr.value_size = create_attr->value_size;
	attr.max_entries = create_attr->max_entries;
	attr.map_flags = create_attr->map_flags;
	if (create_attr->name)
		memcpy(attr.map_name, create_attr->name,
		       min(strlen(create_attr->name), BPF_OBJ_NAME_LEN - 1));
	attr.numa_node = create_attr->numa_node;
	attr.btf_fd = create_attr->btf_fd;
	attr.btf_key_type_id = create_attr->btf_key_type_id;
	attr.btf_value_type_id = create_attr->btf_value_type_id;
	attr.map_ifindex = create_attr->map_ifindex;
	attr.inner_map_fd = create_attr->inner_map_fd;

	return sys_bpf(BPF_MAP_CREATE, &attr, sizeof(attr));
}