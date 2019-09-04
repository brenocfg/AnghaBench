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
struct task_struct {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 struct task_struct* find_early_kill_thread (struct task_struct*) ; 
 scalar_t__ sysctl_memory_failure_early_kill ; 

__attribute__((used)) static struct task_struct *task_early_kill(struct task_struct *tsk,
					   int force_early)
{
	struct task_struct *t;
	if (!tsk->mm)
		return NULL;
	if (force_early)
		return tsk;
	t = find_early_kill_thread(tsk);
	if (t)
		return t;
	if (sysctl_memory_failure_early_kill)
		return tsk;
	return NULL;
}