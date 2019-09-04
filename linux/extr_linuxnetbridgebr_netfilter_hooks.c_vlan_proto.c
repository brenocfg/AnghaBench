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
struct sk_buff {scalar_t__ protocol; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {scalar_t__ h_vlan_encapsulated_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff const*) ; 
 TYPE_1__* vlan_eth_hdr (struct sk_buff const*) ; 

__attribute__((used)) static inline __be16 vlan_proto(const struct sk_buff *skb)
{
	if (skb_vlan_tag_present(skb))
		return skb->protocol;
	else if (skb->protocol == htons(ETH_P_8021Q))
		return vlan_eth_hdr(skb)->h_vlan_encapsulated_proto;
	else
		return 0;
}