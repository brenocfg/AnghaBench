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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_vif_priv {int /*<<< orphan*/  ctx; } ;
struct iwl_station_priv {int client; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  pending_frames; } ;
struct iwl_priv {int dummy; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWL_INVALID_STATION ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_add_station_common (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ieee80211_sta*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwlagn_mac_sta_add(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      struct ieee80211_sta *sta)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	struct iwl_station_priv *sta_priv = (void *)sta->drv_priv;
	struct iwl_vif_priv *vif_priv = (void *)vif->drv_priv;
	bool is_ap = vif->type == NL80211_IFTYPE_STATION;
	int ret;
	u8 sta_id;

	IWL_DEBUG_INFO(priv, "proceeding to add station %pM\n",
			sta->addr);
	sta_priv->sta_id = IWL_INVALID_STATION;

	atomic_set(&sta_priv->pending_frames, 0);
	if (vif->type == NL80211_IFTYPE_AP)
		sta_priv->client = true;

	ret = iwl_add_station_common(priv, vif_priv->ctx, sta->addr,
				     is_ap, sta, &sta_id);
	if (ret) {
		IWL_ERR(priv, "Unable to add station %pM (%d)\n",
			sta->addr, ret);
		/* Should we return success if return code is EEXIST ? */
		return ret;
	}

	sta_priv->sta_id = sta_id;

	return 0;
}