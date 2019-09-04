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
struct task_struct {int dummy; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 long __get_user_pages (struct task_struct*,struct mm_struct*,unsigned long,unsigned long,unsigned int,struct page**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long __get_user_pages_unlocked(struct task_struct *tsk,
			struct mm_struct *mm, unsigned long start,
			unsigned long nr_pages, struct page **pages,
			unsigned int gup_flags)
{
	long ret;
	down_read(&mm->mmap_sem);
	ret = __get_user_pages(tsk, mm, start, nr_pages, gup_flags, pages,
				NULL, NULL);
	up_read(&mm->mmap_sem);
	return ret;
}