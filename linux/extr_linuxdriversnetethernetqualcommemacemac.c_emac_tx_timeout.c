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
struct net_device {int dummy; } ;
struct emac_adapter {int /*<<< orphan*/  work_thread; } ;

/* Variables and functions */
 struct emac_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emac_tx_timeout(struct net_device *netdev)
{
	struct emac_adapter *adpt = netdev_priv(netdev);

	schedule_work(&adpt->work_thread);
}