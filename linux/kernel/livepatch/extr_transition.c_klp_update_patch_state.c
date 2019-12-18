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
struct task_struct {int /*<<< orphan*/  patch_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIF_PATCH_PENDING ; 
 int /*<<< orphan*/  klp_target_state ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 
 scalar_t__ test_and_clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

void klp_update_patch_state(struct task_struct *task)
{
	/*
	 * A variant of synchronize_rcu() is used to allow patching functions
	 * where RCU is not watching, see klp_synchronize_transition().
	 */
	preempt_disable_notrace();

	/*
	 * This test_and_clear_tsk_thread_flag() call also serves as a read
	 * barrier (smp_rmb) for two cases:
	 *
	 * 1) Enforce the order of the TIF_PATCH_PENDING read and the
	 *    klp_target_state read.  The corresponding write barrier is in
	 *    klp_init_transition().
	 *
	 * 2) Enforce the order of the TIF_PATCH_PENDING read and a future read
	 *    of func->transition, if klp_ftrace_handler() is called later on
	 *    the same CPU.  See __klp_disable_patch().
	 */
	if (test_and_clear_tsk_thread_flag(task, TIF_PATCH_PENDING))
		task->patch_state = READ_ONCE(klp_target_state);

	preempt_enable_notrace();
}