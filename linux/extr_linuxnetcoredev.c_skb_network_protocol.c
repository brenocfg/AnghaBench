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
struct sk_buff {scalar_t__ protocol; scalar_t__ data; } ;
struct ethhdr {scalar_t__ h_proto; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TEB ; 
 scalar_t__ __vlan_get_protocol (struct sk_buff*,scalar_t__,int*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__be16 skb_network_protocol(struct sk_buff *skb, int *depth)
{
	__be16 type = skb->protocol;

	/* Tunnel gso handlers can set protocol to ethernet. */
	if (type == htons(ETH_P_TEB)) {
		struct ethhdr *eth;

		if (unlikely(!pskb_may_pull(skb, sizeof(struct ethhdr))))
			return 0;

		eth = (struct ethhdr *)skb->data;
		type = eth->h_proto;
	}

	return __vlan_get_protocol(skb, type, depth);
}