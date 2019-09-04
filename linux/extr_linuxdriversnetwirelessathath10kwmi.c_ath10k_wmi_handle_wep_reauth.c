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
typedef  int u8 ;
struct sk_buff {int* data; unsigned int len; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  flag; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath10k {int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 unsigned int IEEE80211_WEP_IV_LEN ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int WEP_KEYID_SHIFT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int*) ; 
 int ath10k_mac_is_peer_wep_key_set (struct ath10k*,int*,int) ; 
 int* ieee80211_get_SA (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 unsigned int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_auth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_wmi_handle_wep_reauth(struct ath10k *ar,
					 struct sk_buff *skb,
					 struct ieee80211_rx_status *status)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	unsigned int hdrlen;
	bool peer_key;
	u8 *addr, keyidx;

	if (!ieee80211_is_auth(hdr->frame_control) ||
	    !ieee80211_has_protected(hdr->frame_control))
		return;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	if (skb->len < (hdrlen + IEEE80211_WEP_IV_LEN))
		return;

	keyidx = skb->data[hdrlen + (IEEE80211_WEP_IV_LEN - 1)] >> WEP_KEYID_SHIFT;
	addr = ieee80211_get_SA(hdr);

	spin_lock_bh(&ar->data_lock);
	peer_key = ath10k_mac_is_peer_wep_key_set(ar, addr, keyidx);
	spin_unlock_bh(&ar->data_lock);

	if (peer_key) {
		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "mac wep key present for peer %pM\n", addr);
		status->flag |= RX_FLAG_DECRYPTED;
	}
}