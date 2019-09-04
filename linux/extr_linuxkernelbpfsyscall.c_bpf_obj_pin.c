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
union bpf_attr {scalar_t__ file_flags; int /*<<< orphan*/  pathname; int /*<<< orphan*/  bpf_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_OBJ ; 
 scalar_t__ CHECK_ATTR (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int bpf_obj_pin_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_obj_pin(const union bpf_attr *attr)
{
	if (CHECK_ATTR(BPF_OBJ) || attr->file_flags != 0)
		return -EINVAL;

	return bpf_obj_pin_user(attr->bpf_fd, u64_to_user_ptr(attr->pathname));
}