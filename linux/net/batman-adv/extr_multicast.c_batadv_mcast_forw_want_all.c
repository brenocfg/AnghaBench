#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
#define  ETH_P_IP 129 
#define  ETH_P_IPV6 128 
 int NET_XMIT_DROP ; 
 int batadv_mcast_forw_want_all_ipv4 (struct batadv_priv*,struct sk_buff*,unsigned short) ; 
 int batadv_mcast_forw_want_all_ipv6 (struct batadv_priv*,struct sk_buff*,unsigned short) ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
batadv_mcast_forw_want_all(struct batadv_priv *bat_priv,
			   struct sk_buff *skb, unsigned short vid)
{
	switch (ntohs(eth_hdr(skb)->h_proto)) {
	case ETH_P_IP:
		return batadv_mcast_forw_want_all_ipv4(bat_priv, skb, vid);
	case ETH_P_IPV6:
		return batadv_mcast_forw_want_all_ipv6(bat_priv, skb, vid);
	default:
		/* we shouldn't be here... */
		return NET_XMIT_DROP;
	}
}