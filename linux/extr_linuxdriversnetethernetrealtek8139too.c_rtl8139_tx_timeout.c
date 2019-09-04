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
struct rtl8139_private {int watchdog_fired; int /*<<< orphan*/  thread; int /*<<< orphan*/  have_thread; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl8139_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  next_tick ; 
 int /*<<< orphan*/  rtl8139_thread ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8139_tx_timeout (struct net_device *dev)
{
	struct rtl8139_private *tp = netdev_priv(dev);

	tp->watchdog_fired = 1;
	if (!tp->have_thread) {
		INIT_DELAYED_WORK(&tp->thread, rtl8139_thread);
		schedule_delayed_work(&tp->thread, next_tick);
	}
}