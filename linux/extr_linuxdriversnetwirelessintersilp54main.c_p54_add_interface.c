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
struct p54_common {scalar_t__ mode; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  mac_addr; struct ieee80211_vif* vif; } ;
struct ieee80211_vif {int type; int /*<<< orphan*/  addr; int /*<<< orphan*/  driver_flags; } ;
struct ieee80211_hw {struct p54_common* priv; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_VIF_BEACON_FILTER ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int p54_setup_mac (struct p54_common*) ; 

__attribute__((used)) static int p54_add_interface(struct ieee80211_hw *dev,
			     struct ieee80211_vif *vif)
{
	struct p54_common *priv = dev->priv;
	int err;

	vif->driver_flags |= IEEE80211_VIF_BEACON_FILTER;

	mutex_lock(&priv->conf_mutex);
	if (priv->mode != NL80211_IFTYPE_MONITOR) {
		mutex_unlock(&priv->conf_mutex);
		return -EOPNOTSUPP;
	}

	priv->vif = vif;

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_MESH_POINT:
		priv->mode = vif->type;
		break;
	default:
		mutex_unlock(&priv->conf_mutex);
		return -EOPNOTSUPP;
	}

	memcpy(priv->mac_addr, vif->addr, ETH_ALEN);
	err = p54_setup_mac(priv);
	mutex_unlock(&priv->conf_mutex);
	return err;
}