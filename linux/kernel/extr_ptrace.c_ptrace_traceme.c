#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {TYPE_2__* real_parent; scalar_t__ ptrace; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EPERM ; 
 int PF_EXITING ; 
 scalar_t__ PT_PTRACED ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ptrace_link (TYPE_1__*,TYPE_2__*) ; 
 int security_ptrace_traceme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ptrace_traceme(void)
{
	int ret = -EPERM;

	write_lock_irq(&tasklist_lock);
	/* Are we already being traced? */
	if (!current->ptrace) {
		ret = security_ptrace_traceme(current->parent);
		/*
		 * Check PF_EXITING to ensure ->real_parent has not passed
		 * exit_ptrace(). Otherwise we don't report the error but
		 * pretend ->real_parent untraces us right after return.
		 */
		if (!ret && !(current->real_parent->flags & PF_EXITING)) {
			current->ptrace = PT_PTRACED;
			ptrace_link(current, current->real_parent);
		}
	}
	write_unlock_irq(&tasklist_lock);

	return ret;
}