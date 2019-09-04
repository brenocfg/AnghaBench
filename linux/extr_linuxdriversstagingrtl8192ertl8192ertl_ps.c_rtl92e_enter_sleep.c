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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct r8192_priv {int /*<<< orphan*/  ps_lock; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_sleep_wq; int /*<<< orphan*/  hw_wakeup_wq; } ;

/* Variables and functions */
 int MAX_SLEEP_TIME ; 
 int MIN_SLEEP_TIME ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__,unsigned long) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

void rtl92e_enter_sleep(struct net_device *dev, u64 time)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	u32 tmp;
	unsigned long flags;
	unsigned long timeout;

	spin_lock_irqsave(&priv->ps_lock, flags);

	time -= msecs_to_jiffies(8 + 16 + 7);

	timeout = jiffies + msecs_to_jiffies(MIN_SLEEP_TIME);
	if (time_before((unsigned long)time, timeout)) {
		spin_unlock_irqrestore(&priv->ps_lock, flags);
		netdev_info(dev, "too short to sleep::%lld < %ld\n",
			    time - jiffies, msecs_to_jiffies(MIN_SLEEP_TIME));
		return;
	}
	timeout = jiffies + msecs_to_jiffies(MAX_SLEEP_TIME);
	if (time_after((unsigned long)time, timeout)) {
		netdev_info(dev, "========>too long to sleep:%lld > %ld\n",
			    time - jiffies, msecs_to_jiffies(MAX_SLEEP_TIME));
		spin_unlock_irqrestore(&priv->ps_lock, flags);
		return;
	}
	tmp = time - jiffies;
	schedule_delayed_work(&priv->rtllib->hw_wakeup_wq, tmp);
	schedule_delayed_work(&priv->rtllib->hw_sleep_wq, 0);
	spin_unlock_irqrestore(&priv->ps_lock, flags);
}