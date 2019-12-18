#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_4__ {TYPE_3__* mm; } ;

/* Variables and functions */
 unsigned int FOLL_LONGTERM ; 
 int __gup_longterm_locked (TYPE_1__*,TYPE_3__*,unsigned long,int,struct page**,int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int get_user_pages_unlocked (unsigned long,int,struct page**,unsigned int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __gup_longterm_unlocked(unsigned long start, int nr_pages,
				   unsigned int gup_flags, struct page **pages)
{
	int ret;

	/*
	 * FIXME: FOLL_LONGTERM does not work with
	 * get_user_pages_unlocked() (see comments in that function)
	 */
	if (gup_flags & FOLL_LONGTERM) {
		down_read(&current->mm->mmap_sem);
		ret = __gup_longterm_locked(current, current->mm,
					    start, nr_pages,
					    pages, NULL, gup_flags);
		up_read(&current->mm->mmap_sem);
	} else {
		ret = get_user_pages_unlocked(start, nr_pages,
					      pages, gup_flags);
	}

	return ret;
}