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
typedef  scalar_t__ u8 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct lbs_private {scalar_t__ wep_tx_key; struct net_device* mesh_dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  lbs_deb_assoc (char*,scalar_t__) ; 
 int /*<<< orphan*/  lbs_set_wep_keys (struct lbs_private*) ; 
 struct lbs_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int lbs_cfg_set_default_key(struct wiphy *wiphy,
				   struct net_device *netdev,
				   u8 key_index, bool unicast,
				   bool multicast)
{
	struct lbs_private *priv = wiphy_priv(wiphy);

	if (netdev == priv->mesh_dev)
		return -EOPNOTSUPP;

	if (key_index != priv->wep_tx_key) {
		lbs_deb_assoc("set_default_key: to %d\n", key_index);
		priv->wep_tx_key = key_index;
		lbs_set_wep_keys(priv);
	}

	return 0;
}