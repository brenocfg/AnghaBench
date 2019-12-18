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
union bpf_attr {int value_size; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int EINVAL ; 
 int htab_map_alloc_check (union bpf_attr*) ; 

__attribute__((used)) static int fd_htab_map_alloc_check(union bpf_attr *attr)
{
	if (attr->value_size != sizeof(u32))
		return -EINVAL;
	return htab_map_alloc_check(attr);
}