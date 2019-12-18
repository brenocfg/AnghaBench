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
struct TYPE_2__ {struct TYPE_2__* next; } ;
struct task_struct {TYPE_1__ cg_list; } ;
struct css_task_iter {int /*<<< orphan*/  flags; TYPE_1__* task_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSS_TASK_ITER_SKIPPED ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void css_task_iter_skip(struct css_task_iter *it,
			       struct task_struct *task)
{
	lockdep_assert_held(&css_set_lock);

	if (it->task_pos == &task->cg_list) {
		it->task_pos = it->task_pos->next;
		it->flags |= CSS_TASK_ITER_SKIPPED;
	}
}