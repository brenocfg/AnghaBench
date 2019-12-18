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
union bpf_attr {int value_size; int map_flags; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int BPF_F_RDONLY_PROG ; 
 int BPF_F_WRONLY_PROG ; 
 int EINVAL ; 
 int array_map_alloc_check (union bpf_attr*) ; 

__attribute__((used)) static int fd_array_map_alloc_check(union bpf_attr *attr)
{
	/* only file descriptors can be stored in this type of map */
	if (attr->value_size != sizeof(u32))
		return -EINVAL;
	/* Program read-only/write-only not supported for special maps yet. */
	if (attr->map_flags & (BPF_F_RDONLY_PROG | BPF_F_WRONLY_PROG))
		return -EINVAL;
	return array_map_alloc_check(attr);
}