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
struct task_struct {int /*<<< orphan*/  mems_allowed; } ;
struct TYPE_2__ {int /*<<< orphan*/  mems_allowed; int /*<<< orphan*/  cpus_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuset_cgrp_id ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ task_css_is_root (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpuset_fork(struct task_struct *task)
{
	if (task_css_is_root(task, cpuset_cgrp_id))
		return;

	set_cpus_allowed_ptr(task, current->cpus_ptr);
	task->mems_allowed = current->mems_allowed;
}