#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int driver_smps_mode; int /*<<< orphan*/  tdls_peer_del_work; int /*<<< orphan*/  tdls_peer; } ;
struct TYPE_4__ {TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  hw; } ;
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;

/* Variables and functions */
 int EBUSY ; 
 int ENOLINK ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int IEEE80211_SMPS_AUTOMATIC ; 
 int IEEE80211_SMPS_OFF ; 
 int /*<<< orphan*/  TDLS_PEER_SETUP_TIMEOUT ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ieee80211_flush_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ieee80211_tdls_prep_mgmt_packet (struct wiphy*,struct net_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tdls_dbg (struct ieee80211_sub_if_data*,char*,int) ; 

__attribute__((used)) static int
ieee80211_tdls_mgmt_setup(struct wiphy *wiphy, struct net_device *dev,
			  const u8 *peer, u8 action_code, u8 dialog_token,
			  u16 status_code, u32 peer_capability, bool initiator,
			  const u8 *extra_ies, size_t extra_ies_len)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	enum ieee80211_smps_mode smps_mode = sdata->u.mgd.driver_smps_mode;
	int ret;

	/* don't support setup with forced SMPS mode that's not off */
	if (smps_mode != IEEE80211_SMPS_AUTOMATIC &&
	    smps_mode != IEEE80211_SMPS_OFF) {
		tdls_dbg(sdata, "Aborting TDLS setup due to SMPS mode %d\n",
			 smps_mode);
		return -ENOTSUPP;
	}

	mutex_lock(&local->mtx);

	/* we don't support concurrent TDLS peer setups */
	if (!is_zero_ether_addr(sdata->u.mgd.tdls_peer) &&
	    !ether_addr_equal(sdata->u.mgd.tdls_peer, peer)) {
		ret = -EBUSY;
		goto out_unlock;
	}

	/*
	 * make sure we have a STA representing the peer so we drop or buffer
	 * non-TDLS-setup frames to the peer. We can't send other packets
	 * during setup through the AP path.
	 * Allow error packets to be sent - sometimes we don't even add a STA
	 * before failing the setup.
	 */
	if (status_code == 0) {
		rcu_read_lock();
		if (!sta_info_get(sdata, peer)) {
			rcu_read_unlock();
			ret = -ENOLINK;
			goto out_unlock;
		}
		rcu_read_unlock();
	}

	ieee80211_flush_queues(local, sdata, false);
	memcpy(sdata->u.mgd.tdls_peer, peer, ETH_ALEN);
	mutex_unlock(&local->mtx);

	/* we cannot take the mutex while preparing the setup packet */
	ret = ieee80211_tdls_prep_mgmt_packet(wiphy, dev, peer, action_code,
					      dialog_token, status_code,
					      peer_capability, initiator,
					      extra_ies, extra_ies_len, 0,
					      NULL);
	if (ret < 0) {
		mutex_lock(&local->mtx);
		eth_zero_addr(sdata->u.mgd.tdls_peer);
		mutex_unlock(&local->mtx);
		return ret;
	}

	ieee80211_queue_delayed_work(&sdata->local->hw,
				     &sdata->u.mgd.tdls_peer_del_work,
				     TDLS_PEER_SETUP_TIMEOUT);
	return 0;

out_unlock:
	mutex_unlock(&local->mtx);
	return ret;
}