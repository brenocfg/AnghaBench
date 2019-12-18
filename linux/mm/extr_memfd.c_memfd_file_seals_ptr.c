#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct TYPE_4__ {unsigned int seals; } ;
struct TYPE_3__ {unsigned int seals; } ;

/* Variables and functions */
 TYPE_2__* HUGETLBFS_I (int /*<<< orphan*/ ) ; 
 TYPE_1__* SHMEM_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 scalar_t__ is_file_hugepages (struct file*) ; 
 scalar_t__ shmem_file (struct file*) ; 

__attribute__((used)) static unsigned int *memfd_file_seals_ptr(struct file *file)
{
	if (shmem_file(file))
		return &SHMEM_I(file_inode(file))->seals;

#ifdef CONFIG_HUGETLBFS
	if (is_file_hugepages(file))
		return &HUGETLBFS_I(file_inode(file))->seals;
#endif

	return NULL;
}