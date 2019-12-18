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
struct cgroup_root {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 struct cgroup* cset_cgroup_from_root (int /*<<< orphan*/ ,struct cgroup_root*) ; 
 int /*<<< orphan*/  task_css_set (struct task_struct*) ; 

struct cgroup *task_cgroup_from_root(struct task_struct *task,
				     struct cgroup_root *root)
{
	/*
	 * No need to lock the task - since we hold cgroup_mutex the
	 * task can't change groups, so the only thing that can happen
	 * is that it exits and its css is set back to init_css_set.
	 */
	return cset_cgroup_from_root(task_css_set(task), root);
}