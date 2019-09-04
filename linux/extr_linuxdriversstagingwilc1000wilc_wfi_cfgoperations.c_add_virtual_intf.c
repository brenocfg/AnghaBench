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
struct wireless_dev {int /*<<< orphan*/  netdev; } ;
struct wiphy {int dummy; } ;
struct wilc_vif {int monitor_flag; int /*<<< orphan*/  ndev; } ;
struct wilc_priv {struct wireless_dev* wdev; } ;
struct vif_params {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int NL80211_IFTYPE_MONITOR ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 struct net_device* wilc_wfi_init_mon_interface (char const*,int /*<<< orphan*/ ) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static struct wireless_dev *add_virtual_intf(struct wiphy *wiphy,
					     const char *name,
					     unsigned char name_assign_type,
					     enum nl80211_iftype type,
					     struct vif_params *params)
{
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->wdev->netdev);
	struct net_device *new_ifc;

	if (type == NL80211_IFTYPE_MONITOR) {
		new_ifc = wilc_wfi_init_mon_interface(name, vif->ndev);
		if (new_ifc) {
			vif = netdev_priv(priv->wdev->netdev);
			vif->monitor_flag = 1;
		}
	}
	return priv->wdev;
}