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
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 scalar_t__ IEEE80211_QOS_CTL_LEN ; 
 scalar_t__ ieee80211_has_a4 (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath5k_common_padpos(struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	__le16 frame_control = hdr->frame_control;
	int padpos = 24;

	if (ieee80211_has_a4(frame_control))
		padpos += ETH_ALEN;

	if (ieee80211_is_data_qos(frame_control))
		padpos += IEEE80211_QOS_CTL_LEN;

	return padpos;
}