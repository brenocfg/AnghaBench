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
struct task_struct {int /*<<< orphan*/  task_works; } ;
struct callback_head {struct callback_head* next; } ;

/* Variables and functions */
 int ESRCH ; 
 struct callback_head* READ_ONCE (int /*<<< orphan*/ ) ; 
 struct callback_head* cmpxchg (int /*<<< orphan*/ *,struct callback_head*,struct callback_head*) ; 
 int /*<<< orphan*/  set_notify_resume (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 struct callback_head work_exited ; 

int
task_work_add(struct task_struct *task, struct callback_head *work, bool notify)
{
	struct callback_head *head;

	do {
		head = READ_ONCE(task->task_works);
		if (unlikely(head == &work_exited))
			return -ESRCH;
		work->next = head;
	} while (cmpxchg(&task->task_works, head, work) != head);

	if (notify)
		set_notify_resume(task);
	return 0;
}