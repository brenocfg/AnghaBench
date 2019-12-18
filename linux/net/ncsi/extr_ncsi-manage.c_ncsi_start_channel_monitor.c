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
struct TYPE_2__ {int enabled; int /*<<< orphan*/  timer; int /*<<< orphan*/  state; } ;
struct ncsi_channel {TYPE_1__ monitor; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  NCSI_CHANNEL_MONITOR_START ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ncsi_start_channel_monitor(struct ncsi_channel *nc)
{
	unsigned long flags;

	spin_lock_irqsave(&nc->lock, flags);
	WARN_ON_ONCE(nc->monitor.enabled);
	nc->monitor.enabled = true;
	nc->monitor.state = NCSI_CHANNEL_MONITOR_START;
	spin_unlock_irqrestore(&nc->lock, flags);

	mod_timer(&nc->monitor.timer, jiffies + HZ);
}