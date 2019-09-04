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
typedef  int u32 ;
struct xlr_net_priv {int dummy; } ;
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct xlr_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int phy_start_aneg (struct phy_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct phy_device* xlr_get_phydev (struct xlr_net_priv*) ; 
 int /*<<< orphan*/  xlr_set_gmac_speed (struct xlr_net_priv*) ; 

__attribute__((used)) static int xlr_net_open(struct net_device *ndev)
{
	u32 err;
	struct xlr_net_priv *priv = netdev_priv(ndev);
	struct phy_device *phydev = xlr_get_phydev(priv);

	/* schedule a link state check */
	phy_start(phydev);

	err = phy_start_aneg(phydev);
	if (err) {
		pr_err("Autoneg failed\n");
		return err;
	}
	/* Setup the speed from PHY to internal reg*/
	xlr_set_gmac_speed(priv);

	netif_tx_start_all_queues(ndev);

	return 0;
}