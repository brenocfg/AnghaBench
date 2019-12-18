#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_11__ {int type; int /*<<< orphan*/ * addr; } ;
struct TYPE_9__ {TYPE_2__* associated; } ;
struct TYPE_10__ {TYPE_3__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_5__ vif; TYPE_4__ u; struct ieee80211_local* local; } ;
struct TYPE_7__ {scalar_t__ extra_tx_headroom; } ;
struct ieee80211_local {TYPE_1__ hw; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/ * bssid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FCTL_TODS ; 
 int IEEE80211_FTYPE_DATA ; 
 TYPE_6__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_STYPE_DATA ; 
 int /*<<< orphan*/  IEEE80211_TX_INTFL_TKIP_MIC_FAILURE ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_sdata_running (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_tx_skb (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  mac_pton (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdata_lock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  sdata_unlock (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_hdr* skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static ssize_t ieee80211_if_parse_tkip_mic_test(
	struct ieee80211_sub_if_data *sdata, const char *buf, int buflen)
{
	struct ieee80211_local *local = sdata->local;
	u8 addr[ETH_ALEN];
	struct sk_buff *skb;
	struct ieee80211_hdr *hdr;
	__le16 fc;

	if (!mac_pton(buf, addr))
		return -EINVAL;

	if (!ieee80211_sdata_running(sdata))
		return -ENOTCONN;

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + 24 + 100);
	if (!skb)
		return -ENOMEM;
	skb_reserve(skb, local->hw.extra_tx_headroom);

	hdr = skb_put_zero(skb, 24);
	fc = cpu_to_le16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA);

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP:
		fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS);
		/* DA BSSID SA */
		memcpy(hdr->addr1, addr, ETH_ALEN);
		memcpy(hdr->addr2, sdata->vif.addr, ETH_ALEN);
		memcpy(hdr->addr3, sdata->vif.addr, ETH_ALEN);
		break;
	case NL80211_IFTYPE_STATION:
		fc |= cpu_to_le16(IEEE80211_FCTL_TODS);
		/* BSSID SA DA */
		sdata_lock(sdata);
		if (!sdata->u.mgd.associated) {
			sdata_unlock(sdata);
			dev_kfree_skb(skb);
			return -ENOTCONN;
		}
		memcpy(hdr->addr1, sdata->u.mgd.associated->bssid, ETH_ALEN);
		memcpy(hdr->addr2, sdata->vif.addr, ETH_ALEN);
		memcpy(hdr->addr3, addr, ETH_ALEN);
		sdata_unlock(sdata);
		break;
	default:
		dev_kfree_skb(skb);
		return -EOPNOTSUPP;
	}
	hdr->frame_control = fc;

	/*
	 * Add some length to the test frame to make it look bit more valid.
	 * The exact contents does not matter since the recipient is required
	 * to drop this because of the Michael MIC failure.
	 */
	skb_put_zero(skb, 50);

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_TKIP_MIC_FAILURE;

	ieee80211_tx_skb(sdata, skb);

	return buflen;
}