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
struct wcn36xx_vif {int /*<<< orphan*/  list; int /*<<< orphan*/  sta_list; int /*<<< orphan*/  bss_index; } ;
struct wcn36xx {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  vif_list; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 int /*<<< orphan*/  WCN36XX_HAL_BSS_INVALID_IDX ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,struct ieee80211_vif*,scalar_t__) ; 
 int /*<<< orphan*/  wcn36xx_smd_add_sta_self (struct wcn36xx*,struct ieee80211_vif*) ; 
 struct wcn36xx_vif* wcn36xx_vif_to_priv (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*,scalar_t__) ; 

__attribute__((used)) static int wcn36xx_add_interface(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif)
{
	struct wcn36xx *wcn = hw->priv;
	struct wcn36xx_vif *vif_priv = wcn36xx_vif_to_priv(vif);

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac add interface vif %p type %d\n",
		    vif, vif->type);

	if (!(NL80211_IFTYPE_STATION == vif->type ||
	      NL80211_IFTYPE_AP == vif->type ||
	      NL80211_IFTYPE_ADHOC == vif->type ||
	      NL80211_IFTYPE_MESH_POINT == vif->type)) {
		wcn36xx_warn("Unsupported interface type requested: %d\n",
			     vif->type);
		return -EOPNOTSUPP;
	}

	mutex_lock(&wcn->conf_mutex);

	vif_priv->bss_index = WCN36XX_HAL_BSS_INVALID_IDX;
	INIT_LIST_HEAD(&vif_priv->sta_list);
	list_add(&vif_priv->list, &wcn->vif_list);
	wcn36xx_smd_add_sta_self(wcn, vif);

	mutex_unlock(&wcn->conf_mutex);

	return 0;
}