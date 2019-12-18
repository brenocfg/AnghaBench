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
struct task_struct {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  fu_llist; int /*<<< orphan*/  fu_rcuhead; } ;
struct file {TYPE_1__ f_u; int /*<<< orphan*/  f_count; } ;

/* Variables and functions */
 int PF_KTHREAD ; 
 int /*<<< orphan*/  ____fput ; 
 scalar_t__ atomic_long_sub_and_test (unsigned int,int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  delayed_fput_list ; 
 int /*<<< orphan*/  delayed_fput_work ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  init_task_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  task_work_add (struct task_struct*,int /*<<< orphan*/ *,int) ; 

void fput_many(struct file *file, unsigned int refs)
{
	if (atomic_long_sub_and_test(refs, &file->f_count)) {
		struct task_struct *task = current;

		if (likely(!in_interrupt() && !(task->flags & PF_KTHREAD))) {
			init_task_work(&file->f_u.fu_rcuhead, ____fput);
			if (!task_work_add(task, &file->f_u.fu_rcuhead, true))
				return;
			/*
			 * After this task has run exit_task_work(),
			 * task_work_add() will fail.  Fall through to delayed
			 * fput to avoid leaking *file.
			 */
		}

		if (llist_add(&file->f_u.fu_llist, &delayed_fput_list))
			schedule_delayed_work(&delayed_fput_work, 1);
	}
}