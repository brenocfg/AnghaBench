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
struct vm_area_struct {int dummy; } ;
struct task_struct {int dummy; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 unsigned int FOLL_REMOTE ; 
 unsigned int FOLL_TOUCH ; 
 long __get_user_pages_locked (struct task_struct*,struct mm_struct*,unsigned long,unsigned long,struct page**,struct vm_area_struct**,int*,unsigned int) ; 

long get_user_pages_remote(struct task_struct *tsk, struct mm_struct *mm,
		unsigned long start, unsigned long nr_pages,
		unsigned int gup_flags, struct page **pages,
		struct vm_area_struct **vmas, int *locked)
{
	return __get_user_pages_locked(tsk, mm, start, nr_pages, pages, vmas,
				       locked,
				       gup_flags | FOLL_TOUCH | FOLL_REMOTE);
}