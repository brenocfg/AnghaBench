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
union bpf_attr {scalar_t__ map_type; scalar_t__ max_entries; int key_size; scalar_t__ value_size; int map_flags; } ;

/* Variables and functions */
 int ARRAY_CREATE_FLAG_MASK ; 
 scalar_t__ BPF_MAP_TYPE_PERCPU_ARRAY ; 
 int E2BIG ; 
 int EINVAL ; 
 scalar_t__ KMALLOC_MAX_SIZE ; 
 int NUMA_NO_NODE ; 
 int bpf_map_attr_numa_node (union bpf_attr*) ; 
 int /*<<< orphan*/  bpf_map_flags_access_ok (int) ; 

int array_map_alloc_check(union bpf_attr *attr)
{
	bool percpu = attr->map_type == BPF_MAP_TYPE_PERCPU_ARRAY;
	int numa_node = bpf_map_attr_numa_node(attr);

	/* check sanity of attributes */
	if (attr->max_entries == 0 || attr->key_size != 4 ||
	    attr->value_size == 0 ||
	    attr->map_flags & ~ARRAY_CREATE_FLAG_MASK ||
	    !bpf_map_flags_access_ok(attr->map_flags) ||
	    (percpu && numa_node != NUMA_NO_NODE))
		return -EINVAL;

	if (attr->value_size > KMALLOC_MAX_SIZE)
		/* if value_size is bigger, the user space won't be able to
		 * access the elements.
		 */
		return -E2BIG;

	return 0;
}