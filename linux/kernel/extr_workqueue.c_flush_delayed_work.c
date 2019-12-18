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
struct delayed_work {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; int /*<<< orphan*/  cpu; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 

bool flush_delayed_work(struct delayed_work *dwork)
{
	local_irq_disable();
	if (del_timer_sync(&dwork->timer))
		__queue_work(dwork->cpu, dwork->wq, &dwork->work);
	local_irq_enable();
	return flush_work(&dwork->work);
}