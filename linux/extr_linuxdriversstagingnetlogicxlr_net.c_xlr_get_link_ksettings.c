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
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct xlr_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (struct phy_device*,struct ethtool_link_ksettings*) ; 
 struct phy_device* xlr_get_phydev (struct xlr_net_priv*) ; 

__attribute__((used)) static int xlr_get_link_ksettings(struct net_device *ndev,
				  struct ethtool_link_ksettings *ecmd)
{
	struct xlr_net_priv *priv = netdev_priv(ndev);
	struct phy_device *phydev = xlr_get_phydev(priv);

	if (!phydev)
		return -ENODEV;

	phy_ethtool_ksettings_get(phydev, ecmd);

	return 0;
}