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
struct sk_buff {int dummy; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 int batadv_mcast_forw_tt (struct batadv_priv*,struct sk_buff*,unsigned short) ; 
 int batadv_mcast_forw_want_all (struct batadv_priv*,struct sk_buff*,unsigned short) ; 
 int batadv_mcast_forw_want_rtr (struct batadv_priv*,struct sk_buff*,unsigned short) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

int batadv_mcast_forw_send(struct batadv_priv *bat_priv, struct sk_buff *skb,
			   unsigned short vid)
{
	int ret;

	ret = batadv_mcast_forw_tt(bat_priv, skb, vid);
	if (ret != NET_XMIT_SUCCESS) {
		kfree_skb(skb);
		return ret;
	}

	ret = batadv_mcast_forw_want_all(bat_priv, skb, vid);
	if (ret != NET_XMIT_SUCCESS) {
		kfree_skb(skb);
		return ret;
	}

	ret = batadv_mcast_forw_want_rtr(bat_priv, skb, vid);
	if (ret != NET_XMIT_SUCCESS) {
		kfree_skb(skb);
		return ret;
	}

	consume_skb(skb);
	return ret;
}