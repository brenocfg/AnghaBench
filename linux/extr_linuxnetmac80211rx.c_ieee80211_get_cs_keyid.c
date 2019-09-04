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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ieee80211_cipher_scheme {scalar_t__ hdr_len; int key_idx_mask; int key_idx_shift; scalar_t__ key_idx_off; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EINVAL ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,scalar_t__,int*,int) ; 

__attribute__((used)) static int ieee80211_get_cs_keyid(const struct ieee80211_cipher_scheme *cs,
				  struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	__le16 fc;
	int hdrlen;
	u8 keyid;

	fc = hdr->frame_control;
	hdrlen = ieee80211_hdrlen(fc);

	if (skb->len < hdrlen + cs->hdr_len)
		return -EINVAL;

	skb_copy_bits(skb, hdrlen + cs->key_idx_off, &keyid, 1);
	keyid &= cs->key_idx_mask;
	keyid >>= cs->key_idx_shift;

	return keyid;
}