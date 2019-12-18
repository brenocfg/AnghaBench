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
union bpf_attr {scalar_t__ max_entries; scalar_t__ key_size; scalar_t__ value_size; int map_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int E2BIG ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ KMALLOC_MAX_SIZE ; 
 int QUEUE_STACK_CREATE_FLAG_MASK ; 
 int /*<<< orphan*/  bpf_map_flags_access_ok (int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int queue_stack_map_alloc_check(union bpf_attr *attr)
{
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	/* check sanity of attributes */
	if (attr->max_entries == 0 || attr->key_size != 0 ||
	    attr->value_size == 0 ||
	    attr->map_flags & ~QUEUE_STACK_CREATE_FLAG_MASK ||
	    !bpf_map_flags_access_ok(attr->map_flags))
		return -EINVAL;

	if (attr->value_size > KMALLOC_MAX_SIZE)
		/* if value_size is bigger, the user space won't be able to
		 * access the elements.
		 */
		return -E2BIG;

	return 0;
}