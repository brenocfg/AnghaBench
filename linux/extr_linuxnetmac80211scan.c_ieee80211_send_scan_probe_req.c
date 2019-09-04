#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; } ;
struct ieee80211_channel {int /*<<< orphan*/  band; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IEEE80211_PROBE_FLAG_RANDOM_SN ; 
 TYPE_1__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_SN_TO_SEQ (int /*<<< orphan*/ ) ; 
 int IEEE80211_TX_NO_SEQNO ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_u32 () ; 
 struct sk_buff* ieee80211_build_probe_req (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,struct ieee80211_channel*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int) ; 
 int /*<<< orphan*/  ieee80211_tx_skb_tid_band (struct ieee80211_sub_if_data*,struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ieee80211_send_scan_probe_req(struct ieee80211_sub_if_data *sdata,
					  const u8 *src, const u8 *dst,
					  const u8 *ssid, size_t ssid_len,
					  const u8 *ie, size_t ie_len,
					  u32 ratemask, u32 flags, u32 tx_flags,
					  struct ieee80211_channel *channel)
{
	struct sk_buff *skb;
	u32 txdata_flags = 0;

	skb = ieee80211_build_probe_req(sdata, src, dst, ratemask, channel,
					ssid, ssid_len,
					ie, ie_len, flags);

	if (skb) {
		if (flags & IEEE80211_PROBE_FLAG_RANDOM_SN) {
			struct ieee80211_hdr *hdr = (void *)skb->data;
			u16 sn = get_random_u32();

			txdata_flags |= IEEE80211_TX_NO_SEQNO;
			hdr->seq_ctrl =
				cpu_to_le16(IEEE80211_SN_TO_SEQ(sn));
		}
		IEEE80211_SKB_CB(skb)->flags |= tx_flags;
		ieee80211_tx_skb_tid_band(sdata, skb, 7, channel->band,
					  txdata_flags);
	}
}