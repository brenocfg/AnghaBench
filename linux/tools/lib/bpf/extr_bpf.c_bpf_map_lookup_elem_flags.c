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
union bpf_attr {int map_fd; int /*<<< orphan*/  flags; void* value; void* key; } ;
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_LOOKUP_ELEM ; 
 int /*<<< orphan*/  memset (union bpf_attr*,int /*<<< orphan*/ ,int) ; 
 void* ptr_to_u64 (void*) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_map_lookup_elem_flags(int fd, const void *key, void *value, __u64 flags)
{
	union bpf_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.map_fd = fd;
	attr.key = ptr_to_u64(key);
	attr.value = ptr_to_u64(value);
	attr.flags = flags;

	return sys_bpf(BPF_MAP_LOOKUP_ELEM, &attr, sizeof(attr));
}