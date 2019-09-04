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
struct task_struct {TYPE_1__* signal; } ;
struct TYPE_2__ {int has_child_subreaper; } ;

/* Variables and functions */
 scalar_t__ is_child_reaper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid (struct task_struct*) ; 

__attribute__((used)) static int propagate_has_child_subreaper(struct task_struct *p, void *data)
{
	/*
	 * If task has has_child_subreaper - all its decendants
	 * already have these flag too and new decendants will
	 * inherit it on fork, skip them.
	 *
	 * If we've found child_reaper - skip descendants in
	 * it's subtree as they will never get out pidns.
	 */
	if (p->signal->has_child_subreaper ||
	    is_child_reaper(task_pid(p)))
		return 0;

	p->signal->has_child_subreaper = 1;
	return 1;
}