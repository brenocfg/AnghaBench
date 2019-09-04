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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct sta_info {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  IEEE80211_QUEUE_STOP_REASON_TDLS_TEARDOWN ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_PEER_AUTH ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_flush_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_stop_vif_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int ieee80211_tdls_prep_mgmt_packet (struct wiphy*,struct net_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_wake_vif_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sdata_err (struct ieee80211_sub_if_data*,char*,int) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
ieee80211_tdls_mgmt_teardown(struct wiphy *wiphy, struct net_device *dev,
			     const u8 *peer, u8 action_code, u8 dialog_token,
			     u16 status_code, u32 peer_capability,
			     bool initiator, const u8 *extra_ies,
			     size_t extra_ies_len)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;
	int ret;

	/*
	 * No packets can be transmitted to the peer via the AP during setup -
	 * the STA is set as a TDLS peer, but is not authorized.
	 * During teardown, we prevent direct transmissions by stopping the
	 * queues and flushing all direct packets.
	 */
	ieee80211_stop_vif_queues(local, sdata,
				  IEEE80211_QUEUE_STOP_REASON_TDLS_TEARDOWN);
	ieee80211_flush_queues(local, sdata, false);

	ret = ieee80211_tdls_prep_mgmt_packet(wiphy, dev, peer, action_code,
					      dialog_token, status_code,
					      peer_capability, initiator,
					      extra_ies, extra_ies_len, 0,
					      NULL);
	if (ret < 0)
		sdata_err(sdata, "Failed sending TDLS teardown packet %d\n",
			  ret);

	/*
	 * Remove the STA AUTH flag to force further traffic through the AP. If
	 * the STA was unreachable, it was already removed.
	 */
	rcu_read_lock();
	sta = sta_info_get(sdata, peer);
	if (sta)
		clear_sta_flag(sta, WLAN_STA_TDLS_PEER_AUTH);
	rcu_read_unlock();

	ieee80211_wake_vif_queues(local, sdata,
				  IEEE80211_QUEUE_STOP_REASON_TDLS_TEARDOWN);

	return 0;
}