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

/* Variables and functions */
 unsigned int MFD_HUGETLB ; 
 int /*<<< orphan*/  __NR_memfd_create ; 
 scalar_t__ hugetlbfs_test ; 
 int syscall (int /*<<< orphan*/ ,char const*,unsigned int) ; 

int sys_memfd_create(const char *name, unsigned int flags)
{
	if (hugetlbfs_test)
		flags |= MFD_HUGETLB;

	return syscall(__NR_memfd_create, name, flags);
}