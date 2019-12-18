#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u64 ;
struct TYPE_8__ {int /*<<< orphan*/ * packets; int /*<<< orphan*/ * bytes; scalar_t__* msdu; } ;
struct sta_info {TYPE_3__ tx_stats; } ;
struct sk_buff {size_t* data; size_t priority; scalar_t__ len; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_4__* hw_key; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  hw_queue; int /*<<< orphan*/  flags; TYPE_1__ control; } ;
struct TYPE_7__ {int /*<<< orphan*/ * hw_queue; } ;
struct ieee80211_sub_if_data {int sequence_number; TYPE_2__ vif; } ;
struct TYPE_9__ {int cipher; int keyidx; int /*<<< orphan*/  tx_pn; } ;
struct ieee80211_key {TYPE_4__ conf; } ;
struct ieee80211_hdr {int frame_control; int seq_ctrl; } ;
struct TYPE_10__ {scalar_t__ gso_size; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (scalar_t__,scalar_t__) ; 
 size_t IEEE80211_NUM_TIDS ; 
 size_t IEEE80211_QOS_CTL_TAG1D_MASK ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_STYPE_QOS_DATA ; 
 int /*<<< orphan*/  IEEE80211_TX_CTL_ASSIGN_SEQ ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_CCMP_256 130 
#define  WLAN_CIPHER_SUITE_GCMP 129 
#define  WLAN_CIPHER_SUITE_GCMP_256 128 
 int atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int cpu_to_le16 (int) ; 
 int ieee80211_tx_next_seq (struct sta_info*,size_t) ; 
 int /*<<< orphan*/  ieee80211_tx_stats (int /*<<< orphan*/ ,scalar_t__) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 TYPE_5__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void ieee80211_xmit_fast_finish(struct ieee80211_sub_if_data *sdata,
				       struct sta_info *sta, u8 pn_offs,
				       struct ieee80211_key *key,
				       struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hdr *hdr = (void *)skb->data;
	u8 tid = IEEE80211_NUM_TIDS;

	if (key)
		info->control.hw_key = &key->conf;

	ieee80211_tx_stats(skb->dev, skb->len);

	if (hdr->frame_control & cpu_to_le16(IEEE80211_STYPE_QOS_DATA)) {
		tid = skb->priority & IEEE80211_QOS_CTL_TAG1D_MASK;
		hdr->seq_ctrl = ieee80211_tx_next_seq(sta, tid);
	} else {
		info->flags |= IEEE80211_TX_CTL_ASSIGN_SEQ;
		hdr->seq_ctrl = cpu_to_le16(sdata->sequence_number);
		sdata->sequence_number += 0x10;
	}

	if (skb_shinfo(skb)->gso_size)
		sta->tx_stats.msdu[tid] +=
			DIV_ROUND_UP(skb->len, skb_shinfo(skb)->gso_size);
	else
		sta->tx_stats.msdu[tid]++;

	info->hw_queue = sdata->vif.hw_queue[skb_get_queue_mapping(skb)];

	/* statistics normally done by ieee80211_tx_h_stats (but that
	 * has to consider fragmentation, so is more complex)
	 */
	sta->tx_stats.bytes[skb_get_queue_mapping(skb)] += skb->len;
	sta->tx_stats.packets[skb_get_queue_mapping(skb)]++;

	if (pn_offs) {
		u64 pn;
		u8 *crypto_hdr = skb->data + pn_offs;

		switch (key->conf.cipher) {
		case WLAN_CIPHER_SUITE_CCMP:
		case WLAN_CIPHER_SUITE_CCMP_256:
		case WLAN_CIPHER_SUITE_GCMP:
		case WLAN_CIPHER_SUITE_GCMP_256:
			pn = atomic64_inc_return(&key->conf.tx_pn);
			crypto_hdr[0] = pn;
			crypto_hdr[1] = pn >> 8;
			crypto_hdr[3] = 0x20 | (key->conf.keyidx << 6);
			crypto_hdr[4] = pn >> 16;
			crypto_hdr[5] = pn >> 24;
			crypto_hdr[6] = pn >> 32;
			crypto_hdr[7] = pn >> 40;
			break;
		}
	}
}