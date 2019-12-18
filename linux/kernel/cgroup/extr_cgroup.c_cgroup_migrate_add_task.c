#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int flags; int /*<<< orphan*/  cg_list; } ;
struct css_set {TYPE_1__* mg_dst_cset; int /*<<< orphan*/  mg_node; int /*<<< orphan*/  mg_tasks; int /*<<< orphan*/  mg_src_cgrp; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst_csets; int /*<<< orphan*/  src_csets; int /*<<< orphan*/  nr_tasks; } ;
struct cgroup_mgctx {TYPE_2__ tset; } ;
struct TYPE_3__ {int /*<<< orphan*/  mg_node; } ;

/* Variables and functions */
 int PF_EXITING ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct css_set* task_css_set (struct task_struct*) ; 

__attribute__((used)) static void cgroup_migrate_add_task(struct task_struct *task,
				    struct cgroup_mgctx *mgctx)
{
	struct css_set *cset;

	lockdep_assert_held(&css_set_lock);

	/* @task either already exited or can't exit until the end */
	if (task->flags & PF_EXITING)
		return;

	/* leave @task alone if post_fork() hasn't linked it yet */
	if (list_empty(&task->cg_list))
		return;

	cset = task_css_set(task);
	if (!cset->mg_src_cgrp)
		return;

	mgctx->tset.nr_tasks++;

	list_move_tail(&task->cg_list, &cset->mg_tasks);
	if (list_empty(&cset->mg_node))
		list_add_tail(&cset->mg_node,
			      &mgctx->tset.src_csets);
	if (list_empty(&cset->mg_dst_cset->mg_node))
		list_add_tail(&cset->mg_dst_cset->mg_node,
			      &mgctx->tset.dst_csets);
}