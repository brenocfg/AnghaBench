#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int __do_munmap (struct mm_struct*,unsigned long,size_t,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* current ; 
 scalar_t__ down_write_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uf ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userfaultfd_unmap_complete (struct mm_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __vm_munmap(unsigned long start, size_t len, bool downgrade)
{
	int ret;
	struct mm_struct *mm = current->mm;
	LIST_HEAD(uf);

	if (down_write_killable(&mm->mmap_sem))
		return -EINTR;

	ret = __do_munmap(mm, start, len, &uf, downgrade);
	/*
	 * Returning 1 indicates mmap_sem is downgraded.
	 * But 1 is not legal return value of vm_munmap() and munmap(), reset
	 * it to 0 before return.
	 */
	if (ret == 1) {
		up_read(&mm->mmap_sem);
		ret = 0;
	} else
		up_write(&mm->mmap_sem);

	userfaultfd_unmap_complete(mm, &uf);
	return ret;
}