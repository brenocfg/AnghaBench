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
struct cgroup {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int frozen; int jobctl; TYPE_1__* sighand; } ;
struct TYPE_4__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_FREEZE ; 
 int JOBCTL_TRAP_FREEZE ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cgroup_dec_frozen_cnt (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_update_frozen (struct cgroup*) ; 
 int /*<<< orphan*/  css_set_lock ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct cgroup* task_dfl_cgroup (TYPE_2__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cgroup_leave_frozen(bool always_leave)
{
	struct cgroup *cgrp;

	spin_lock_irq(&css_set_lock);
	cgrp = task_dfl_cgroup(current);
	if (always_leave || !test_bit(CGRP_FREEZE, &cgrp->flags)) {
		cgroup_dec_frozen_cnt(cgrp);
		cgroup_update_frozen(cgrp);
		WARN_ON_ONCE(!current->frozen);
		current->frozen = false;
	} else if (!(current->jobctl & JOBCTL_TRAP_FREEZE)) {
		spin_lock(&current->sighand->siglock);
		current->jobctl |= JOBCTL_TRAP_FREEZE;
		set_thread_flag(TIF_SIGPENDING);
		spin_unlock(&current->sighand->siglock);
	}
	spin_unlock_irq(&css_set_lock);
}