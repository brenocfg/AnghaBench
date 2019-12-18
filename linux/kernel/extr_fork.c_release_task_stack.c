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
struct task_struct {scalar_t__ state; int /*<<< orphan*/ * stack_vm_area; int /*<<< orphan*/ * stack; } ;

/* Variables and functions */
 scalar_t__ TASK_DEAD ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  account_kernel_stack (struct task_struct*,int) ; 
 int /*<<< orphan*/  free_thread_stack (struct task_struct*) ; 

__attribute__((used)) static void release_task_stack(struct task_struct *tsk)
{
	if (WARN_ON(tsk->state != TASK_DEAD))
		return;  /* Better to leak the stack than to free prematurely */

	account_kernel_stack(tsk, -1);
	free_thread_stack(tsk);
	tsk->stack = NULL;
#ifdef CONFIG_VMAP_STACK
	tsk->stack_vm_area = NULL;
#endif
}