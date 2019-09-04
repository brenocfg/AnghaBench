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
struct task_struct {int /*<<< orphan*/  blocked; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_2__ {int /*<<< orphan*/  blocked; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  recalc_sigpending () ; 
 int /*<<< orphan*/  retarget_shared_pending (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigandnsets (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (struct task_struct*) ; 
 int /*<<< orphan*/  thread_group_empty (struct task_struct*) ; 

__attribute__((used)) static void __set_task_blocked(struct task_struct *tsk, const sigset_t *newset)
{
	if (signal_pending(tsk) && !thread_group_empty(tsk)) {
		sigset_t newblocked;
		/* A set of now blocked but previously unblocked signals. */
		sigandnsets(&newblocked, newset, &current->blocked);
		retarget_shared_pending(tsk, &newblocked);
	}
	tsk->blocked = *newset;
	recalc_sigpending();
}