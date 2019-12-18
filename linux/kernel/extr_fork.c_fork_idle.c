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
struct kernel_clone_args {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_VM ; 
 int /*<<< orphan*/  IS_ERR (struct task_struct*) ; 
 struct task_struct* copy_process (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kernel_clone_args*) ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  init_idle (struct task_struct*,int) ; 
 int /*<<< orphan*/  init_idle_pids (struct task_struct*) ; 
 int /*<<< orphan*/  init_struct_pid ; 

struct task_struct *fork_idle(int cpu)
{
	struct task_struct *task;
	struct kernel_clone_args args = {
		.flags = CLONE_VM,
	};

	task = copy_process(&init_struct_pid, 0, cpu_to_node(cpu), &args);
	if (!IS_ERR(task)) {
		init_idle_pids(task);
		init_idle(task, cpu);
	}

	return task;
}