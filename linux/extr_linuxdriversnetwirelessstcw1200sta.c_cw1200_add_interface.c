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
struct ieee80211_vif {int driver_flags; int type; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct cw1200_common {scalar_t__ mode; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  mac_addr; struct ieee80211_vif* vif; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_VIF_BEACON_FILTER ; 
 int IEEE80211_VIF_SUPPORTS_CQM_RSSI ; 
 int IEEE80211_VIF_SUPPORTS_UAPSD ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
#define  NL80211_IFTYPE_STATION 128 
 int cw1200_setup_mac (struct cw1200_common*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cw1200_add_interface(struct ieee80211_hw *dev,
			 struct ieee80211_vif *vif)
{
	int ret;
	struct cw1200_common *priv = dev->priv;
	/* __le32 auto_calibration_mode = __cpu_to_le32(1); */

	vif->driver_flags |= IEEE80211_VIF_BEACON_FILTER |
			     IEEE80211_VIF_SUPPORTS_UAPSD |
			     IEEE80211_VIF_SUPPORTS_CQM_RSSI;

	mutex_lock(&priv->conf_mutex);

	if (priv->mode != NL80211_IFTYPE_MONITOR) {
		mutex_unlock(&priv->conf_mutex);
		return -EOPNOTSUPP;
	}

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_MESH_POINT:
	case NL80211_IFTYPE_AP:
		priv->mode = vif->type;
		break;
	default:
		mutex_unlock(&priv->conf_mutex);
		return -EOPNOTSUPP;
	}

	priv->vif = vif;
	memcpy(priv->mac_addr, vif->addr, ETH_ALEN);
	ret = cw1200_setup_mac(priv);
	/* Enable auto-calibration */
	/* Exception in subsequent channel switch; disabled.
	 *  wsm_write_mib(priv, WSM_MIB_ID_SET_AUTO_CALIBRATION_MODE,
	 *      &auto_calibration_mode, sizeof(auto_calibration_mode));
	*/

	mutex_unlock(&priv->conf_mutex);
	return ret;
}