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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__* hw_key; } ;
struct ieee80211_tx_info {TYPE_2__ control; } ;
struct ieee80211_local {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FCTL_PROTECTED ; 
 int IEEE80211_KEY_FLAG_PUT_IV_SPACE ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 scalar_t__ IEEE80211_WEP_IV_LEN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 unsigned int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wep_get_iv (struct ieee80211_local*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_push (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static u8 *ieee80211_wep_add_iv(struct ieee80211_local *local,
				struct sk_buff *skb,
				int keylen, int keyidx)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	unsigned int hdrlen;
	u8 *newhdr;

	hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PROTECTED);

	if (WARN_ON(skb_headroom(skb) < IEEE80211_WEP_IV_LEN))
		return NULL;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	newhdr = skb_push(skb, IEEE80211_WEP_IV_LEN);
	memmove(newhdr, newhdr + IEEE80211_WEP_IV_LEN, hdrlen);

	/* the HW only needs room for the IV, but not the actual IV */
	if (info->control.hw_key &&
	    (info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE))
		return newhdr + hdrlen;

	ieee80211_wep_get_iv(local, keylen, keyidx, newhdr + hdrlen);
	return newhdr + hdrlen;
}