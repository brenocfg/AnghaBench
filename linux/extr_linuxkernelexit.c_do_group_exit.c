#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct signal_struct {int group_exit_code; int /*<<< orphan*/  flags; } ;
struct sighand_struct {int /*<<< orphan*/  siglock; } ;
struct TYPE_4__ {struct sighand_struct* sighand; struct signal_struct* signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SIGNAL_GROUP_EXIT ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  do_exit (int) ; 
 scalar_t__ signal_group_exit (struct signal_struct*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_group_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  zap_other_threads (TYPE_1__*) ; 

void
do_group_exit(int exit_code)
{
	struct signal_struct *sig = current->signal;

	BUG_ON(exit_code & 0x80); /* core dumps don't get here */

	if (signal_group_exit(sig))
		exit_code = sig->group_exit_code;
	else if (!thread_group_empty(current)) {
		struct sighand_struct *const sighand = current->sighand;

		spin_lock_irq(&sighand->siglock);
		if (signal_group_exit(sig))
			/* Another thread got here before we took the lock.  */
			exit_code = sig->group_exit_code;
		else {
			sig->group_exit_code = exit_code;
			sig->flags = SIGNAL_GROUP_EXIT;
			zap_other_threads(current);
		}
		spin_unlock_irq(&sighand->siglock);
	}

	do_exit(exit_code);
	/* NOTREACHED */
}