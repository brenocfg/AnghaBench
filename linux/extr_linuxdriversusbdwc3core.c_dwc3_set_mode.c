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
typedef  int /*<<< orphan*/  u32 ;
struct dwc3 {int /*<<< orphan*/  drd_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  desired_dr_role; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_freezable_wq ; 

void dwc3_set_mode(struct dwc3 *dwc, u32 mode)
{
	unsigned long flags;

	spin_lock_irqsave(&dwc->lock, flags);
	dwc->desired_dr_role = mode;
	spin_unlock_irqrestore(&dwc->lock, flags);

	queue_work(system_freezable_wq, &dwc->drd_work);
}