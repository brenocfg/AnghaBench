#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct iwl_rxon_context {int dummy; } ;
struct iwl_priv {int /*<<< orphan*/  sta_lock; TYPE_2__* stations; } ;
struct iwl_addsta_cmd {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_4__ {size_t const* addr; } ;
struct TYPE_6__ {TYPE_1__ sta; } ;
struct TYPE_5__ {int used; TYPE_3__ sta; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  IWL_DEBUG_ASSOC (struct iwl_priv*,char*,size_t,size_t const*) ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,size_t) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,size_t const*) ; 
 size_t IWL_INVALID_STATION ; 
 int IWL_STA_DRIVER_ACTIVE ; 
 int IWL_STA_UCODE_ACTIVE ; 
 int IWL_STA_UCODE_INPROGRESS ; 
 size_t iwl_prep_station (struct iwl_priv*,struct iwl_rxon_context*,size_t const*,int,struct ieee80211_sta*) ; 
 int iwl_send_add_sta (struct iwl_priv*,struct iwl_addsta_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct iwl_addsta_cmd*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iwl_add_station_common(struct iwl_priv *priv, struct iwl_rxon_context *ctx,
			   const u8 *addr, bool is_ap,
			   struct ieee80211_sta *sta, u8 *sta_id_r)
{
	int ret = 0;
	u8 sta_id;
	struct iwl_addsta_cmd sta_cmd;

	*sta_id_r = 0;
	spin_lock_bh(&priv->sta_lock);
	sta_id = iwl_prep_station(priv, ctx, addr, is_ap, sta);
	if (sta_id == IWL_INVALID_STATION) {
		IWL_ERR(priv, "Unable to prepare station %pM for addition\n",
			addr);
		spin_unlock_bh(&priv->sta_lock);
		return -EINVAL;
	}

	/*
	 * uCode is not able to deal with multiple requests to add a
	 * station. Keep track if one is in progress so that we do not send
	 * another.
	 */
	if (priv->stations[sta_id].used & IWL_STA_UCODE_INPROGRESS) {
		IWL_DEBUG_INFO(priv, "STA %d already in process of being "
			       "added.\n", sta_id);
		spin_unlock_bh(&priv->sta_lock);
		return -EEXIST;
	}

	if ((priv->stations[sta_id].used & IWL_STA_DRIVER_ACTIVE) &&
	    (priv->stations[sta_id].used & IWL_STA_UCODE_ACTIVE)) {
		IWL_DEBUG_ASSOC(priv, "STA %d (%pM) already added, not "
				"adding again.\n", sta_id, addr);
		spin_unlock_bh(&priv->sta_lock);
		return -EEXIST;
	}

	priv->stations[sta_id].used |= IWL_STA_UCODE_INPROGRESS;
	memcpy(&sta_cmd, &priv->stations[sta_id].sta,
	       sizeof(struct iwl_addsta_cmd));
	spin_unlock_bh(&priv->sta_lock);

	/* Add station to device's station table */
	ret = iwl_send_add_sta(priv, &sta_cmd, 0);
	if (ret) {
		spin_lock_bh(&priv->sta_lock);
		IWL_ERR(priv, "Adding station %pM failed.\n",
			priv->stations[sta_id].sta.sta.addr);
		priv->stations[sta_id].used &= ~IWL_STA_DRIVER_ACTIVE;
		priv->stations[sta_id].used &= ~IWL_STA_UCODE_INPROGRESS;
		spin_unlock_bh(&priv->sta_lock);
	}
	*sta_id_r = sta_id;
	return ret;
}