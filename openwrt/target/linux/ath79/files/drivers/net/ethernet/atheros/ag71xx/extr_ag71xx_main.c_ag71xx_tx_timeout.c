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
struct net_device {int dummy; } ;
struct ag71xx {int /*<<< orphan*/  restart_work; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct ag71xx* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_tx_err (struct ag71xx*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ag71xx_tx_timeout(struct net_device *dev)
{
	struct ag71xx *ag = netdev_priv(dev);

	if (netif_msg_tx_err(ag))
		pr_info("%s: tx timeout\n", ag->dev->name);

	schedule_delayed_work(&ag->restart_work, 1);
}