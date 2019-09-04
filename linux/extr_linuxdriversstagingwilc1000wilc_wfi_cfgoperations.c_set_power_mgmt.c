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
struct wiphy {int dummy; } ;
struct wilc_vif {int dummy; } ;
struct wilc_priv {int /*<<< orphan*/  hif_drv; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ wilc_enable_ps ; 
 int /*<<< orphan*/  wilc_set_power_mgmt (struct wilc_vif*,int,int) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int set_power_mgmt(struct wiphy *wiphy, struct net_device *dev,
			  bool enabled, int timeout)
{
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->dev);

	if (!priv->hif_drv)
		return -EIO;

	if (wilc_enable_ps)
		wilc_set_power_mgmt(vif, enabled, timeout);

	return 0;
}