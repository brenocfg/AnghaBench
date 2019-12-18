#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_13__ {scalar_t__ vht_supported; } ;
struct TYPE_14__ {scalar_t__ ht_supported; } ;
struct TYPE_12__ {TYPE_6__ vht_cap; TYPE_7__ ht_cap; scalar_t__ wme; } ;
struct sta_info {int /*<<< orphan*/  tdls_chandef; TYPE_5__ sta; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_vht_operation {int dummy; } ;
struct ieee80211_supported_band {scalar_t__ band; } ;
struct TYPE_10__ {int /*<<< orphan*/  chandef; } ;
struct TYPE_11__ {TYPE_3__ bss_conf; } ;
struct ieee80211_if_managed {int /*<<< orphan*/  const* bssid; } ;
struct TYPE_8__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_4__ vif; TYPE_1__ u; struct ieee80211_local* local; } ;
struct TYPE_9__ {scalar_t__ queues; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_mtx; TYPE_2__ hw; } ;
struct ieee80211_ht_operation {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT ; 
 int IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT ; 
 int IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED ; 
 scalar_t__ IEEE80211_NUM_ACS ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
#define  WLAN_EID_FAST_BSS_TRANSITION 131 
#define  WLAN_EID_QOS_CAPA 130 
#define  WLAN_EID_RSN 129 
#define  WLAN_EID_TIMEOUT_INTERVAL 128 
 int /*<<< orphan*/  WLAN_STA_TDLS_WIDER_BW ; 
 struct ieee80211_supported_band* ieee80211_get_sband (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_ie_build_ht_oper (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ieee80211_ie_build_vht_oper (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *) ; 
 size_t ieee80211_ie_split (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ieee80211_tdls_add_link_ie (struct ieee80211_sub_if_data*,struct sk_buff*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ieee80211_tdls_add_wmm_param_ie (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tdls_chandef_vht_upgrade (struct ieee80211_sub_if_data*,struct sta_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/  const*,size_t) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ieee80211_tdls_add_setup_cfm_ies(struct ieee80211_sub_if_data *sdata,
				 struct sk_buff *skb, const u8 *peer,
				 bool initiator, const u8 *extra_ies,
				 size_t extra_ies_len)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	size_t offset = 0, noffset;
	struct sta_info *sta, *ap_sta;
	struct ieee80211_supported_band *sband;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		return;

	mutex_lock(&local->sta_mtx);

	sta = sta_info_get(sdata, peer);
	ap_sta = sta_info_get(sdata, ifmgd->bssid);
	if (WARN_ON_ONCE(!sta || !ap_sta)) {
		mutex_unlock(&local->sta_mtx);
		return;
	}

	sta->tdls_chandef = sdata->vif.bss_conf.chandef;

	/* add any custom IEs that go before the QoS IE */
	if (extra_ies_len) {
		static const u8 before_qos[] = {
			WLAN_EID_RSN,
		};
		noffset = ieee80211_ie_split(extra_ies, extra_ies_len,
					     before_qos,
					     ARRAY_SIZE(before_qos),
					     offset);
		skb_put_data(skb, extra_ies + offset, noffset - offset);
		offset = noffset;
	}

	/* add the QoS param IE if both the peer and we support it */
	if (local->hw.queues >= IEEE80211_NUM_ACS && sta->sta.wme)
		ieee80211_tdls_add_wmm_param_ie(sdata, skb);

	/* add any custom IEs that go before HT operation */
	if (extra_ies_len) {
		static const u8 before_ht_op[] = {
			WLAN_EID_RSN,
			WLAN_EID_QOS_CAPA,
			WLAN_EID_FAST_BSS_TRANSITION,
			WLAN_EID_TIMEOUT_INTERVAL,
		};
		noffset = ieee80211_ie_split(extra_ies, extra_ies_len,
					     before_ht_op,
					     ARRAY_SIZE(before_ht_op),
					     offset);
		skb_put_data(skb, extra_ies + offset, noffset - offset);
		offset = noffset;
	}

	/*
	 * if HT support is only added in TDLS, we need an HT-operation IE.
	 * add the IE as required by IEEE802.11-2012 9.23.3.2.
	 */
	if (!ap_sta->sta.ht_cap.ht_supported && sta->sta.ht_cap.ht_supported) {
		u16 prot = IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED |
			   IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT |
			   IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT;

		pos = skb_put(skb, 2 + sizeof(struct ieee80211_ht_operation));
		ieee80211_ie_build_ht_oper(pos, &sta->sta.ht_cap,
					   &sdata->vif.bss_conf.chandef, prot,
					   true);
	}

	ieee80211_tdls_add_link_ie(sdata, skb, peer, initiator);

	/* only include VHT-operation if not on the 2.4GHz band */
	if (sband->band != NL80211_BAND_2GHZ &&
	    sta->sta.vht_cap.vht_supported) {
		/*
		 * if both peers support WIDER_BW, we can expand the chandef to
		 * a wider compatible one, up to 80MHz
		 */
		if (test_sta_flag(sta, WLAN_STA_TDLS_WIDER_BW))
			ieee80211_tdls_chandef_vht_upgrade(sdata, sta);

		pos = skb_put(skb, 2 + sizeof(struct ieee80211_vht_operation));
		ieee80211_ie_build_vht_oper(pos, &sta->sta.vht_cap,
					    &sta->tdls_chandef);
	}

	mutex_unlock(&local->sta_mtx);

	/* add any remaining IEs */
	if (extra_ies_len) {
		noffset = extra_ies_len;
		skb_put_data(skb, extra_ies + offset, noffset - offset);
	}
}