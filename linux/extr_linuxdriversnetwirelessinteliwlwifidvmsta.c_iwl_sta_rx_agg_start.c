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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_priv {int /*<<< orphan*/  sta_lock; TYPE_2__* stations; int /*<<< orphan*/  mutex; } ;
struct iwl_addsta_cmd {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  modify_mask; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  add_immediate_ba_ssn; scalar_t__ add_immediate_ba_tid; TYPE_1__ sta; scalar_t__ station_flags_msk; } ;
struct TYPE_5__ {TYPE_3__ sta; } ;

/* Variables and functions */
 int ENXIO ; 
 int IWL_INVALID_STATION ; 
 int /*<<< orphan*/  STA_CONTROL_MODIFY_MSK ; 
 int /*<<< orphan*/  STA_MODIFY_ADDBA_TID_MSK ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int iwl_send_add_sta (struct iwl_priv*,struct iwl_addsta_cmd*,int /*<<< orphan*/ ) ; 
 int iwl_sta_id (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct iwl_addsta_cmd*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iwl_sta_rx_agg_start(struct iwl_priv *priv, struct ieee80211_sta *sta,
			 int tid, u16 ssn)
{
	int sta_id;
	struct iwl_addsta_cmd sta_cmd;

	lockdep_assert_held(&priv->mutex);

	sta_id = iwl_sta_id(sta);
	if (sta_id == IWL_INVALID_STATION)
		return -ENXIO;

	spin_lock_bh(&priv->sta_lock);
	priv->stations[sta_id].sta.station_flags_msk = 0;
	priv->stations[sta_id].sta.sta.modify_mask = STA_MODIFY_ADDBA_TID_MSK;
	priv->stations[sta_id].sta.add_immediate_ba_tid = (u8)tid;
	priv->stations[sta_id].sta.add_immediate_ba_ssn = cpu_to_le16(ssn);
	priv->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	memcpy(&sta_cmd, &priv->stations[sta_id].sta, sizeof(struct iwl_addsta_cmd));
	spin_unlock_bh(&priv->sta_lock);

	return iwl_send_add_sta(priv, &sta_cmd, 0);
}