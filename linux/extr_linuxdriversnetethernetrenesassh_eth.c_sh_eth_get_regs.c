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
struct sh_eth_private {TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int /*<<< orphan*/  version; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SH_ETH_REG_DUMP_VERSION ; 
 int /*<<< orphan*/  __sh_eth_get_regs (struct net_device*,void*) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sh_eth_get_regs(struct net_device *ndev, struct ethtool_regs *regs,
			    void *buf)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);

	regs->version = SH_ETH_REG_DUMP_VERSION;

	pm_runtime_get_sync(&mdp->pdev->dev);
	__sh_eth_get_regs(ndev, buf);
	pm_runtime_put_sync(&mdp->pdev->dev);
}