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
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 scalar_t__ in_group_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_hugetlb_shm_group ; 

__attribute__((used)) static int can_do_hugetlb_shm(void)
{
	kgid_t shm_group;
	shm_group = make_kgid(&init_user_ns, sysctl_hugetlb_shm_group);
	return capable(CAP_IPC_LOCK) || in_group_p(shm_group);
}