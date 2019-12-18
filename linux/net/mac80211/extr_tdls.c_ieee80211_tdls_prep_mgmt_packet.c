#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int const u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct TYPE_5__ {int tdls_initiator; } ;
struct sta_info {TYPE_1__ sta; } ;
struct sk_buff {int priority; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  teardown_lock; struct sk_buff* orig_teardown_skb; int /*<<< orphan*/  teardown_skb; } ;
struct TYPE_8__ {TYPE_3__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_2__* local; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int IEEE80211_TX_INTFL_MLME_CONN_TX ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
#define  WLAN_PUB_ACTION_TDLS_DISCOVER_RES 135 
 int /*<<< orphan*/  WLAN_STA_TDLS_INITIATOR ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_PEER_AUTH ; 
#define  WLAN_TDLS_CHANNEL_SWITCH_REQUEST 134 
#define  WLAN_TDLS_CHANNEL_SWITCH_RESPONSE 133 
#define  WLAN_TDLS_DISCOVERY_REQUEST 132 
#define  WLAN_TDLS_SETUP_CONFIRM 131 
#define  WLAN_TDLS_SETUP_REQUEST 130 
#define  WLAN_TDLS_SETUP_RESPONSE 129 
#define  WLAN_TDLS_TEARDOWN 128 
 int /*<<< orphan*/  __ieee80211_subif_start_xmit (struct sk_buff*,struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_select_queue (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 struct sk_buff* ieee80211_tdls_build_mgmt_packet_data (struct ieee80211_sub_if_data*,int const*,int const,int const,int /*<<< orphan*/ ,int,int const*,size_t,int const,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  ieee80211_tx_skb (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int const*) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ieee80211_tdls_prep_mgmt_packet(struct wiphy *wiphy, struct net_device *dev,
				const u8 *peer, u8 action_code, u8 dialog_token,
				u16 status_code, u32 peer_capability,
				bool initiator, const u8 *extra_ies,
				size_t extra_ies_len, u8 oper_class,
				struct cfg80211_chan_def *chandef)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct sk_buff *skb = NULL;
	struct sta_info *sta;
	u32 flags = 0;
	int ret = 0;

	rcu_read_lock();
	sta = sta_info_get(sdata, peer);

	/* infer the initiator if we can, to support old userspace */
	switch (action_code) {
	case WLAN_TDLS_SETUP_REQUEST:
		if (sta) {
			set_sta_flag(sta, WLAN_STA_TDLS_INITIATOR);
			sta->sta.tdls_initiator = false;
		}
		/* fall-through */
	case WLAN_TDLS_SETUP_CONFIRM:
	case WLAN_TDLS_DISCOVERY_REQUEST:
		initiator = true;
		break;
	case WLAN_TDLS_SETUP_RESPONSE:
		/*
		 * In some testing scenarios, we send a request and response.
		 * Make the last packet sent take effect for the initiator
		 * value.
		 */
		if (sta) {
			clear_sta_flag(sta, WLAN_STA_TDLS_INITIATOR);
			sta->sta.tdls_initiator = true;
		}
		/* fall-through */
	case WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		initiator = false;
		break;
	case WLAN_TDLS_TEARDOWN:
	case WLAN_TDLS_CHANNEL_SWITCH_REQUEST:
	case WLAN_TDLS_CHANNEL_SWITCH_RESPONSE:
		/* any value is ok */
		break;
	default:
		ret = -ENOTSUPP;
		break;
	}

	if (sta && test_sta_flag(sta, WLAN_STA_TDLS_INITIATOR))
		initiator = true;

	rcu_read_unlock();
	if (ret < 0)
		goto fail;

	skb = ieee80211_tdls_build_mgmt_packet_data(sdata, peer, action_code,
						    dialog_token, status_code,
						    initiator, extra_ies,
						    extra_ies_len, oper_class,
						    chandef);
	if (!skb) {
		ret = -EINVAL;
		goto fail;
	}

	if (action_code == WLAN_PUB_ACTION_TDLS_DISCOVER_RES) {
		ieee80211_tx_skb(sdata, skb);
		return 0;
	}

	/*
	 * According to 802.11z: Setup req/resp are sent in AC_BK, otherwise
	 * we should default to AC_VI.
	 */
	switch (action_code) {
	case WLAN_TDLS_SETUP_REQUEST:
	case WLAN_TDLS_SETUP_RESPONSE:
		skb->priority = 256 + 2;
		break;
	default:
		skb->priority = 256 + 5;
		break;
	}
	skb_set_queue_mapping(skb, ieee80211_select_queue(sdata, skb));

	/*
	 * Set the WLAN_TDLS_TEARDOWN flag to indicate a teardown in progress.
	 * Later, if no ACK is returned from peer, we will re-send the teardown
	 * packet through the AP.
	 */
	if ((action_code == WLAN_TDLS_TEARDOWN) &&
	    ieee80211_hw_check(&sdata->local->hw, REPORTS_TX_ACK_STATUS)) {
		bool try_resend; /* Should we keep skb for possible resend */

		/* If not sending directly to peer - no point in keeping skb */
		rcu_read_lock();
		sta = sta_info_get(sdata, peer);
		try_resend = sta && test_sta_flag(sta, WLAN_STA_TDLS_PEER_AUTH);
		rcu_read_unlock();

		spin_lock_bh(&sdata->u.mgd.teardown_lock);
		if (try_resend && !sdata->u.mgd.teardown_skb) {
			/* Mark it as requiring TX status callback  */
			flags |= IEEE80211_TX_CTL_REQ_TX_STATUS |
				 IEEE80211_TX_INTFL_MLME_CONN_TX;

			/*
			 * skb is copied since mac80211 will later set
			 * properties that might not be the same as the AP,
			 * such as encryption, QoS, addresses, etc.
			 *
			 * No problem if skb_copy() fails, so no need to check.
			 */
			sdata->u.mgd.teardown_skb = skb_copy(skb, GFP_ATOMIC);
			sdata->u.mgd.orig_teardown_skb = skb;
		}
		spin_unlock_bh(&sdata->u.mgd.teardown_lock);
	}

	/* disable bottom halves when entering the Tx path */
	local_bh_disable();
	__ieee80211_subif_start_xmit(skb, dev, flags, 0);
	local_bh_enable();

	return ret;

fail:
	dev_kfree_skb(skb);
	return ret;
}