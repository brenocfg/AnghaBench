#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_3__ {struct mm_struct* mm; } ;

/* Variables and functions */
 long EINVAL ; 
 unsigned int FOLL_LONGTERM ; 
 unsigned int FOLL_TOUCH ; 
 scalar_t__ WARN_ON_ONCE (unsigned int) ; 
 long __get_user_pages_locked (TYPE_1__*,struct mm_struct*,unsigned long,unsigned long,struct page**,int /*<<< orphan*/ *,int*,unsigned int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

long get_user_pages_unlocked(unsigned long start, unsigned long nr_pages,
			     struct page **pages, unsigned int gup_flags)
{
	struct mm_struct *mm = current->mm;
	int locked = 1;
	long ret;

	/*
	 * FIXME: Current FOLL_LONGTERM behavior is incompatible with
	 * FAULT_FLAG_ALLOW_RETRY because of the FS DAX check requirement on
	 * vmas.  As there are no users of this flag in this call we simply
	 * disallow this option for now.
	 */
	if (WARN_ON_ONCE(gup_flags & FOLL_LONGTERM))
		return -EINVAL;

	down_read(&mm->mmap_sem);
	ret = __get_user_pages_locked(current, mm, start, nr_pages, pages, NULL,
				      &locked, gup_flags | FOLL_TOUCH);
	if (locked)
		up_read(&mm->mmap_sem);
	return ret;
}