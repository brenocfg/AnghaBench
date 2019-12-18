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
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_rx_data {int /*<<< orphan*/  tkip_iv16; int /*<<< orphan*/  tkip_iv32; int /*<<< orphan*/  security_idx; TYPE_3__* sta; TYPE_1__* local; struct sk_buff* skb; struct ieee80211_key* key; } ;
struct ieee80211_key {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  ieee80211_rx_result ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;
struct TYPE_4__ {int /*<<< orphan*/  wep_rx_ctx; } ;

/* Variables and functions */
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 scalar_t__ IEEE80211_TKIP_ICV_LEN ; 
 scalar_t__ IEEE80211_TKIP_IV_LEN ; 
 int /*<<< orphan*/  RX_CONTINUE ; 
 int /*<<< orphan*/  RX_DROP_UNUSABLE ; 
 int RX_FLAG_DECRYPTED ; 
 int RX_FLAG_ICV_STRIPPED ; 
 int TKIP_DECRYPT_OK ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int ieee80211_tkip_decrypt_data (int /*<<< orphan*/ *,struct ieee80211_key*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

ieee80211_rx_result
ieee80211_crypto_tkip_decrypt(struct ieee80211_rx_data *rx)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) rx->skb->data;
	int hdrlen, res, hwaccel = 0;
	struct ieee80211_key *key = rx->key;
	struct sk_buff *skb = rx->skb;
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);

	hdrlen = ieee80211_hdrlen(hdr->frame_control);

	if (!ieee80211_is_data(hdr->frame_control))
		return RX_CONTINUE;

	if (!rx->sta || skb->len - hdrlen < 12)
		return RX_DROP_UNUSABLE;

	/* it may be possible to optimize this a bit more */
	if (skb_linearize(rx->skb))
		return RX_DROP_UNUSABLE;
	hdr = (void *)skb->data;

	/*
	 * Let TKIP code verify IV, but skip decryption.
	 * In the case where hardware checks the IV as well,
	 * we don't even get here, see ieee80211_rx_h_decrypt()
	 */
	if (status->flag & RX_FLAG_DECRYPTED)
		hwaccel = 1;

	res = ieee80211_tkip_decrypt_data(&rx->local->wep_rx_ctx,
					  key, skb->data + hdrlen,
					  skb->len - hdrlen, rx->sta->sta.addr,
					  hdr->addr1, hwaccel, rx->security_idx,
					  &rx->tkip_iv32,
					  &rx->tkip_iv16);
	if (res != TKIP_DECRYPT_OK)
		return RX_DROP_UNUSABLE;

	/* Trim ICV */
	if (!(status->flag & RX_FLAG_ICV_STRIPPED))
		skb_trim(skb, skb->len - IEEE80211_TKIP_ICV_LEN);

	/* Remove IV */
	memmove(skb->data + IEEE80211_TKIP_IV_LEN, skb->data, hdrlen);
	skb_pull(skb, IEEE80211_TKIP_IV_LEN);

	return RX_CONTINUE;
}