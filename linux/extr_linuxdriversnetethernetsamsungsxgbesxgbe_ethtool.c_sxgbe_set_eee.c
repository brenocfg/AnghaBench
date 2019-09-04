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
struct sxgbe_priv_data {int /*<<< orphan*/  tx_lpi_timer; scalar_t__ eee_enabled; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;
struct ethtool_eee {int /*<<< orphan*/  tx_lpi_timer; scalar_t__ eee_enabled; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct sxgbe_priv_data* netdev_priv (struct net_device*) ; 
 int phy_ethtool_set_eee (int /*<<< orphan*/ ,struct ethtool_eee*) ; 
 int /*<<< orphan*/  sxgbe_disable_eee_mode (struct sxgbe_priv_data*) ; 
 scalar_t__ sxgbe_eee_init (struct sxgbe_priv_data*) ; 

__attribute__((used)) static int sxgbe_set_eee(struct net_device *dev,
			 struct ethtool_eee *edata)
{
	struct sxgbe_priv_data *priv = netdev_priv(dev);

	priv->eee_enabled = edata->eee_enabled;

	if (!priv->eee_enabled) {
		sxgbe_disable_eee_mode(priv);
	} else {
		/* We are asking for enabling the EEE but it is safe
		 * to verify all by invoking the eee_init function.
		 * In case of failure it will return an error.
		 */
		priv->eee_enabled = sxgbe_eee_init(priv);
		if (!priv->eee_enabled)
			return -EOPNOTSUPP;

		/* Do not change tx_lpi_timer in case of failure */
		priv->tx_lpi_timer = edata->tx_lpi_timer;
	}

	return phy_ethtool_set_eee(dev->phydev, edata);
}