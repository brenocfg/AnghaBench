#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {scalar_t__ expires; } ;
struct TYPE_3__ {struct timer_list* timer; } ;
struct mv_otg {TYPE_2__* pdev; TYPE_1__ otg_ctrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned int OTG_TIMER_NUM ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ timer_pending (struct timer_list*) ; 

__attribute__((used)) static int mv_otg_set_timer(struct mv_otg *mvotg, unsigned int id,
			    unsigned long interval)
{
	struct timer_list *timer;

	if (id >= OTG_TIMER_NUM)
		return -EINVAL;

	timer = &mvotg->otg_ctrl.timer[id];
	if (timer_pending(timer)) {
		dev_err(&mvotg->pdev->dev, "Timer%d is already running\n", id);
		return -EBUSY;
	}

	timer->expires = jiffies + interval;
	add_timer(timer);

	return 0;
}