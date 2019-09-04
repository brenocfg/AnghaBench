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
struct task_struct {int /*<<< orphan*/ * mm; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  enter_lazy_tlb (struct mm_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  sync_mm_rss (struct mm_struct*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

void unuse_mm(struct mm_struct *mm)
{
	struct task_struct *tsk = current;

	task_lock(tsk);
	sync_mm_rss(mm);
	tsk->mm = NULL;
	/* active_mm is still 'mm' */
	enter_lazy_tlb(mm, tsk);
	task_unlock(tsk);
}