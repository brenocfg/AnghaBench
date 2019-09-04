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
struct TYPE_2__ {int /*<<< orphan*/  eee; } ;
struct sxgbe_priv_data {int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  eee_active; int /*<<< orphan*/  eee_enabled; TYPE_1__ hw_cap; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;
struct ethtool_eee {int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  eee_active; int /*<<< orphan*/  eee_enabled; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct sxgbe_priv_data* netdev_priv (struct net_device*) ; 
 int phy_ethtool_get_eee (int /*<<< orphan*/ ,struct ethtool_eee*) ; 

__attribute__((used)) static int sxgbe_get_eee(struct net_device *dev,
			 struct ethtool_eee *edata)
{
	struct sxgbe_priv_data *priv = netdev_priv(dev);

	if (!priv->hw_cap.eee)
		return -EOPNOTSUPP;

	edata->eee_enabled = priv->eee_enabled;
	edata->eee_active = priv->eee_active;
	edata->tx_lpi_timer = priv->tx_lpi_timer;

	return phy_ethtool_get_eee(dev->phydev, edata);
}