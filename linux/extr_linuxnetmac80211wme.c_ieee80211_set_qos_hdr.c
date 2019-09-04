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
struct sk_buff {int priority; scalar_t__ data; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; } ;
struct ieee80211_sub_if_data {int noack_map; int /*<<< orphan*/  vif; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IEEE80211_QOS_CTL_ACK_POLICY_MASK ; 
 int IEEE80211_QOS_CTL_ACK_POLICY_NOACK ; 
 int IEEE80211_QOS_CTL_MESH_CONTROL_PRESENT ; 
 int IEEE80211_QOS_CTL_MESH_PS_LEVEL ; 
 int IEEE80211_QOS_CTL_RSPI ; 
 int IEEE80211_QOS_CTL_TAG1D_MASK ; 
 int IEEE80211_QOS_CTL_TID_MASK ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_CTL_NO_ACK ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_qos_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_vif_is_mesh (int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

void ieee80211_set_qos_hdr(struct ieee80211_sub_if_data *sdata,
			   struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (void *)skb->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 tid = skb->priority & IEEE80211_QOS_CTL_TAG1D_MASK;
	u8 flags;
	u8 *p;

	if (!ieee80211_is_data_qos(hdr->frame_control))
		return;

	p = ieee80211_get_qos_ctl(hdr);

	/* set up the first byte */

	/*
	 * preserve everything but the TID and ACK policy
	 * (which we both write here)
	 */
	flags = *p & ~(IEEE80211_QOS_CTL_TID_MASK |
		       IEEE80211_QOS_CTL_ACK_POLICY_MASK);

	if (is_multicast_ether_addr(hdr->addr1) ||
	    sdata->noack_map & BIT(tid)) {
		flags |= IEEE80211_QOS_CTL_ACK_POLICY_NOACK;
		info->flags |= IEEE80211_TX_CTL_NO_ACK;
	}

	*p = flags | tid;

	/* set up the second byte */
	p++;

	if (ieee80211_vif_is_mesh(&sdata->vif)) {
		/* preserve RSPI and Mesh PS Level bit */
		*p &= ((IEEE80211_QOS_CTL_RSPI |
			IEEE80211_QOS_CTL_MESH_PS_LEVEL) >> 8);

		/* Nulls don't have a mesh header (frame body) */
		if (!ieee80211_is_qos_nullfunc(hdr->frame_control))
			*p |= (IEEE80211_QOS_CTL_MESH_CONTROL_PRESENT >> 8);
	} else {
		*p = 0;
	}
}