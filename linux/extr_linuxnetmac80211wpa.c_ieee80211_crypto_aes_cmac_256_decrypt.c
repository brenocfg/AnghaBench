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
struct sk_buff {int data; int len; } ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_rx_data {struct ieee80211_key* key; struct sk_buff* skb; } ;
struct ieee80211_mmie_16 {scalar_t__ element_id; int length; int /*<<< orphan*/  mic; int /*<<< orphan*/  sequence_number; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_pn; int /*<<< orphan*/  icverrors; int /*<<< orphan*/  tfm; int /*<<< orphan*/  replays; } ;
struct TYPE_4__ {TYPE_1__ aes_cmac; } ;
struct ieee80211_key {TYPE_2__ u; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  ieee80211_rx_result ;

/* Variables and functions */
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  RX_CONTINUE ; 
 int /*<<< orphan*/  RX_DROP_UNUSABLE ; 
 int RX_FLAG_DECRYPTED ; 
 scalar_t__ WLAN_EID_MMIE ; 
 int /*<<< orphan*/  bip_aad (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bip_ipn_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_aes_cmac_256 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

ieee80211_rx_result
ieee80211_crypto_aes_cmac_256_decrypt(struct ieee80211_rx_data *rx)
{
	struct sk_buff *skb = rx->skb;
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	struct ieee80211_key *key = rx->key;
	struct ieee80211_mmie_16 *mmie;
	u8 aad[20], mic[16], ipn[6];
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;

	if (!ieee80211_is_mgmt(hdr->frame_control))
		return RX_CONTINUE;

	/* management frames are already linear */

	if (skb->len < 24 + sizeof(*mmie))
		return RX_DROP_UNUSABLE;

	mmie = (struct ieee80211_mmie_16 *)
		(skb->data + skb->len - sizeof(*mmie));
	if (mmie->element_id != WLAN_EID_MMIE ||
	    mmie->length != sizeof(*mmie) - 2)
		return RX_DROP_UNUSABLE; /* Invalid MMIE */

	bip_ipn_swap(ipn, mmie->sequence_number);

	if (memcmp(ipn, key->u.aes_cmac.rx_pn, 6) <= 0) {
		key->u.aes_cmac.replays++;
		return RX_DROP_UNUSABLE;
	}

	if (!(status->flag & RX_FLAG_DECRYPTED)) {
		/* hardware didn't decrypt/verify MIC */
		bip_aad(skb, aad);
		ieee80211_aes_cmac_256(key->u.aes_cmac.tfm, aad,
				       skb->data + 24, skb->len - 24, mic);
		if (crypto_memneq(mic, mmie->mic, sizeof(mmie->mic))) {
			key->u.aes_cmac.icverrors++;
			return RX_DROP_UNUSABLE;
		}
	}

	memcpy(key->u.aes_cmac.rx_pn, ipn, 6);

	/* Remove MMIE */
	skb_trim(skb, skb->len - sizeof(*mmie));

	return RX_CONTINUE;
}