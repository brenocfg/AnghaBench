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
struct mm_struct {int def_flags; int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int VM_LOCKED ; 
 TYPE_1__* current ; 
 int do_brk_flags (unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ down_write_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_populate (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  uf ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userfaultfd_unmap_complete (struct mm_struct*,int /*<<< orphan*/ *) ; 

int vm_brk_flags(unsigned long addr, unsigned long request, unsigned long flags)
{
	struct mm_struct *mm = current->mm;
	unsigned long len;
	int ret;
	bool populate;
	LIST_HEAD(uf);

	len = PAGE_ALIGN(request);
	if (len < request)
		return -ENOMEM;
	if (!len)
		return 0;

	if (down_write_killable(&mm->mmap_sem))
		return -EINTR;

	ret = do_brk_flags(addr, len, flags, &uf);
	populate = ((mm->def_flags & VM_LOCKED) != 0);
	up_write(&mm->mmap_sem);
	userfaultfd_unmap_complete(mm, &uf);
	if (populate && !ret)
		mm_populate(addr, len);
	return ret;
}