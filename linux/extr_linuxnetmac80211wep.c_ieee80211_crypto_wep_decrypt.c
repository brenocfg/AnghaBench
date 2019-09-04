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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_rx_data {struct sk_buff* skb; int /*<<< orphan*/  key; int /*<<< orphan*/  local; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  ieee80211_rx_result ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 scalar_t__ IEEE80211_WEP_ICV_LEN ; 
 scalar_t__ IEEE80211_WEP_IV_LEN ; 
 int /*<<< orphan*/  RX_CONTINUE ; 
 int /*<<< orphan*/  RX_DROP_UNUSABLE ; 
 int RX_FLAG_DECRYPTED ; 
 int RX_FLAG_ICV_STRIPPED ; 
 int RX_FLAG_IV_STRIPPED ; 
 scalar_t__ ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_auth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_wep_decrypt (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wep_remove_iv (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ pskb_trim (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 

ieee80211_rx_result
ieee80211_crypto_wep_decrypt(struct ieee80211_rx_data *rx)
{
	struct sk_buff *skb = rx->skb;
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	__le16 fc = hdr->frame_control;

	if (!ieee80211_is_data(fc) && !ieee80211_is_auth(fc))
		return RX_CONTINUE;

	if (!(status->flag & RX_FLAG_DECRYPTED)) {
		if (skb_linearize(rx->skb))
			return RX_DROP_UNUSABLE;
		if (ieee80211_wep_decrypt(rx->local, rx->skb, rx->key))
			return RX_DROP_UNUSABLE;
	} else if (!(status->flag & RX_FLAG_IV_STRIPPED)) {
		if (!pskb_may_pull(rx->skb, ieee80211_hdrlen(fc) +
					    IEEE80211_WEP_IV_LEN))
			return RX_DROP_UNUSABLE;
		ieee80211_wep_remove_iv(rx->local, rx->skb, rx->key);
		/* remove ICV */
		if (!(status->flag & RX_FLAG_ICV_STRIPPED) &&
		    pskb_trim(rx->skb, rx->skb->len - IEEE80211_WEP_ICV_LEN))
			return RX_DROP_UNUSABLE;
	}

	return RX_CONTINUE;
}