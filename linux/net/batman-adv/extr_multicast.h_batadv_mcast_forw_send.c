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
 int NET_XMIT_DROP ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static inline int
batadv_mcast_forw_send(struct batadv_priv *bat_priv, struct sk_buff *skb,
		       unsigned short vid)
{
	kfree_skb(skb);
	return NET_XMIT_DROP;
}