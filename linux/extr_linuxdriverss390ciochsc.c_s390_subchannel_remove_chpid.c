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
struct subchannel {int /*<<< orphan*/  schid; int /*<<< orphan*/  lock; scalar_t__ lpm; TYPE_1__* driver; } ;
struct TYPE_2__ {scalar_t__ (* chp_event ) (struct subchannel*,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHP_OFFLINE ; 
 int /*<<< orphan*/  css_schedule_eval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct subchannel*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s390_subchannel_remove_chpid(struct subchannel *sch, void *data)
{
	spin_lock_irq(sch->lock);
	if (sch->driver && sch->driver->chp_event)
		if (sch->driver->chp_event(sch, data, CHP_OFFLINE) != 0)
			goto out_unreg;
	spin_unlock_irq(sch->lock);
	return 0;

out_unreg:
	sch->lpm = 0;
	spin_unlock_irq(sch->lock);
	css_schedule_eval(sch->schid);
	return 0;
}