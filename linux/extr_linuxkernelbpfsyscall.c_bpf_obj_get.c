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
union bpf_attr {scalar_t__ bpf_fd; int file_flags; int /*<<< orphan*/  pathname; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_OBJ ; 
 int BPF_OBJ_FLAG_MASK ; 
 scalar_t__ CHECK_ATTR (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int bpf_obj_get_user (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_obj_get(const union bpf_attr *attr)
{
	if (CHECK_ATTR(BPF_OBJ) || attr->bpf_fd != 0 ||
	    attr->file_flags & ~BPF_OBJ_FLAG_MASK)
		return -EINVAL;

	return bpf_obj_get_user(u64_to_user_ptr(attr->pathname),
				attr->file_flags);
}