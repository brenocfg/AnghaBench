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

/* Variables and functions */
 int /*<<< orphan*/  freezer_lock ; 
 scalar_t__ frozen (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

void __thaw_task(struct task_struct *p)
{
	unsigned long flags;

	spin_lock_irqsave(&freezer_lock, flags);
	if (frozen(p))
		wake_up_process(p);
	spin_unlock_irqrestore(&freezer_lock, flags);
}