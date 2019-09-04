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
struct task_struct {int /*<<< orphan*/  pi_lock; int /*<<< orphan*/  flags; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_NO_SETAFFINITY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  do_set_cpus_allowed (struct task_struct*,struct cpumask const*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_task_inactive (struct task_struct*,long) ; 

__attribute__((used)) static void __kthread_bind_mask(struct task_struct *p, const struct cpumask *mask, long state)
{
	unsigned long flags;

	if (!wait_task_inactive(p, state)) {
		WARN_ON(1);
		return;
	}

	/* It's safe because the task is inactive. */
	raw_spin_lock_irqsave(&p->pi_lock, flags);
	do_set_cpus_allowed(p, mask);
	p->flags |= PF_NO_SETAFFINITY;
	raw_spin_unlock_irqrestore(&p->pi_lock, flags);
}