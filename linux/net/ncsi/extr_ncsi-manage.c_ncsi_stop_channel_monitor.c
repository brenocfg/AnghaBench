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
struct TYPE_2__ {int enabled; int /*<<< orphan*/  timer; } ;
struct ncsi_channel {TYPE_1__ monitor; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ncsi_stop_channel_monitor(struct ncsi_channel *nc)
{
	unsigned long flags;

	spin_lock_irqsave(&nc->lock, flags);
	if (!nc->monitor.enabled) {
		spin_unlock_irqrestore(&nc->lock, flags);
		return;
	}
	nc->monitor.enabled = false;
	spin_unlock_irqrestore(&nc->lock, flags);

	del_timer_sync(&nc->monitor.timer);
}