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
struct rfkill {int polling_paused; int /*<<< orphan*/  poll_work; scalar_t__ suspended; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

void rfkill_resume_polling(struct rfkill *rfkill)
{
	BUG_ON(!rfkill);

	if (!rfkill->ops->poll)
		return;

	rfkill->polling_paused = false;

	if (rfkill->suspended)
		return;

	queue_delayed_work(system_power_efficient_wq,
			   &rfkill->poll_work, 0);
}