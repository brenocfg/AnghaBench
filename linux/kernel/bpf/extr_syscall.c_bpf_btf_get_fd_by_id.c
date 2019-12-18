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
union bpf_attr {int /*<<< orphan*/  btf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_BTF_GET_FD_BY_ID ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ CHECK_ATTR (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EPERM ; 
 int btf_get_fd_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_btf_get_fd_by_id(const union bpf_attr *attr)
{
	if (CHECK_ATTR(BPF_BTF_GET_FD_BY_ID))
		return -EINVAL;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	return btf_get_fd_by_id(attr->btf_id);
}