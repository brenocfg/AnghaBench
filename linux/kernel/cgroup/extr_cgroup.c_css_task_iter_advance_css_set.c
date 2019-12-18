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
struct css_task_iter {int /*<<< orphan*/  iters_node; struct css_set* cur_cset; TYPE_1__* dying_tasks_head; TYPE_1__* mg_tasks_head; TYPE_1__* tasks_head; int /*<<< orphan*/ * task_pos; } ;
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;
struct css_set {int /*<<< orphan*/  task_iters; TYPE_1__ dying_tasks; TYPE_1__ mg_tasks; TYPE_1__ tasks; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  css_set_populated (struct css_set*) ; 
 struct css_set* css_task_iter_next_css_set (struct css_task_iter*) ; 
 int /*<<< orphan*/  get_css_set (struct css_set*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_css_set_locked (struct css_set*) ; 

__attribute__((used)) static void css_task_iter_advance_css_set(struct css_task_iter *it)
{
	struct css_set *cset;

	lockdep_assert_held(&css_set_lock);

	/* Advance to the next non-empty css_set */
	do {
		cset = css_task_iter_next_css_set(it);
		if (!cset) {
			it->task_pos = NULL;
			return;
		}
	} while (!css_set_populated(cset) && list_empty(&cset->dying_tasks));

	if (!list_empty(&cset->tasks))
		it->task_pos = cset->tasks.next;
	else if (!list_empty(&cset->mg_tasks))
		it->task_pos = cset->mg_tasks.next;
	else
		it->task_pos = cset->dying_tasks.next;

	it->tasks_head = &cset->tasks;
	it->mg_tasks_head = &cset->mg_tasks;
	it->dying_tasks_head = &cset->dying_tasks;

	/*
	 * We don't keep css_sets locked across iteration steps and thus
	 * need to take steps to ensure that iteration can be resumed after
	 * the lock is re-acquired.  Iteration is performed at two levels -
	 * css_sets and tasks in them.
	 *
	 * Once created, a css_set never leaves its cgroup lists, so a
	 * pinned css_set is guaranteed to stay put and we can resume
	 * iteration afterwards.
	 *
	 * Tasks may leave @cset across iteration steps.  This is resolved
	 * by registering each iterator with the css_set currently being
	 * walked and making css_set_move_task() advance iterators whose
	 * next task is leaving.
	 */
	if (it->cur_cset) {
		list_del(&it->iters_node);
		put_css_set_locked(it->cur_cset);
	}
	get_css_set(cset);
	it->cur_cset = cset;
	list_add(&it->iters_node, &cset->task_iters);
}