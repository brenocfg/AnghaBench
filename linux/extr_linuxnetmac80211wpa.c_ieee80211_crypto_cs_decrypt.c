#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_rx_data {TYPE_4__* skb; TYPE_1__* sta; struct ieee80211_key* key; } ;
struct TYPE_9__ {size_t** rx_pn; } ;
struct TYPE_10__ {TYPE_2__ gen; } ;
struct ieee80211_key {TYPE_3__ u; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ieee80211_cipher_scheme {int hdr_len; int pn_off; scalar_t__ mic_len; int /*<<< orphan*/  pn_len; } ;
typedef  int /*<<< orphan*/  ieee80211_rx_result ;
struct TYPE_11__ {size_t* data; int len; } ;
struct TYPE_8__ {struct ieee80211_cipher_scheme* cipher_scheme; } ;

/* Variables and functions */
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (TYPE_4__*) ; 
 int /*<<< orphan*/  RX_CONTINUE ; 
 int /*<<< orphan*/  RX_DROP_UNUSABLE ; 
 int RX_FLAG_DECRYPTED ; 
 scalar_t__ ieee80211_crypto_cs_pn_compare (size_t*,size_t*,int /*<<< orphan*/ ) ; 
 size_t ieee80211_get_tid (struct ieee80211_hdr*) ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (size_t*,size_t*,int) ; 
 scalar_t__ pskb_trim (TYPE_4__*,scalar_t__) ; 
 scalar_t__ skb_linearize (TYPE_4__*) ; 
 int /*<<< orphan*/  skb_pull (TYPE_4__*,int) ; 

__attribute__((used)) static ieee80211_rx_result
ieee80211_crypto_cs_decrypt(struct ieee80211_rx_data *rx)
{
	struct ieee80211_key *key = rx->key;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)rx->skb->data;
	const struct ieee80211_cipher_scheme *cs = NULL;
	int hdrlen = ieee80211_hdrlen(hdr->frame_control);
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);
	int data_len;
	u8 *rx_pn;
	u8 *skb_pn;
	u8 qos_tid;

	if (!rx->sta || !rx->sta->cipher_scheme ||
	    !(status->flag & RX_FLAG_DECRYPTED))
		return RX_DROP_UNUSABLE;

	if (!ieee80211_is_data(hdr->frame_control))
		return RX_CONTINUE;

	cs = rx->sta->cipher_scheme;

	data_len = rx->skb->len - hdrlen - cs->hdr_len;

	if (data_len < 0)
		return RX_DROP_UNUSABLE;

	if (ieee80211_is_data_qos(hdr->frame_control))
		qos_tid = ieee80211_get_tid(hdr);
	else
		qos_tid = 0;

	if (skb_linearize(rx->skb))
		return RX_DROP_UNUSABLE;

	hdr = (struct ieee80211_hdr *)rx->skb->data;

	rx_pn = key->u.gen.rx_pn[qos_tid];
	skb_pn = rx->skb->data + hdrlen + cs->pn_off;

	if (ieee80211_crypto_cs_pn_compare(skb_pn, rx_pn, cs->pn_len) <= 0)
		return RX_DROP_UNUSABLE;

	memcpy(rx_pn, skb_pn, cs->pn_len);

	/* remove security header and MIC */
	if (pskb_trim(rx->skb, rx->skb->len - cs->mic_len))
		return RX_DROP_UNUSABLE;

	memmove(rx->skb->data + cs->hdr_len, rx->skb->data, hdrlen);
	skb_pull(rx->skb, cs->hdr_len);

	return RX_CONTINUE;
}