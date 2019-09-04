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
struct xlr_net_priv {int dummy; } ;
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct xlr_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (struct phy_device*) ; 
 struct phy_device* xlr_get_phydev (struct xlr_net_priv*) ; 

__attribute__((used)) static int xlr_net_stop(struct net_device *ndev)
{
	struct xlr_net_priv *priv = netdev_priv(ndev);
	struct phy_device *phydev = xlr_get_phydev(priv);

	phy_stop(phydev);
	netif_tx_stop_all_queues(ndev);
	return 0;
}