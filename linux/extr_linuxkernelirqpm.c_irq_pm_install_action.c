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
struct irqaction {int flags; } ;
struct irq_desc {scalar_t__ nr_actions; scalar_t__ force_resume_depth; scalar_t__ no_suspend_depth; scalar_t__ cond_suspend_depth; } ;

/* Variables and functions */
 int IRQF_COND_SUSPEND ; 
 int IRQF_FORCE_RESUME ; 
 int IRQF_NO_SUSPEND ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

void irq_pm_install_action(struct irq_desc *desc, struct irqaction *action)
{
	desc->nr_actions++;

	if (action->flags & IRQF_FORCE_RESUME)
		desc->force_resume_depth++;

	WARN_ON_ONCE(desc->force_resume_depth &&
		     desc->force_resume_depth != desc->nr_actions);

	if (action->flags & IRQF_NO_SUSPEND)
		desc->no_suspend_depth++;
	else if (action->flags & IRQF_COND_SUSPEND)
		desc->cond_suspend_depth++;

	WARN_ON_ONCE(desc->no_suspend_depth &&
		     (desc->no_suspend_depth +
			desc->cond_suspend_depth) != desc->nr_actions);
}