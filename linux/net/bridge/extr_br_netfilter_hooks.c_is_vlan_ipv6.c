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
struct net {int dummy; } ;
struct brnf_net {scalar_t__ filter_vlan_tagged; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  brnf_net_id ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct brnf_net* net_generic (struct net const*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlan_proto (struct sk_buff const*) ; 

__attribute__((used)) static inline bool is_vlan_ipv6(const struct sk_buff *skb,
				const struct net *net)
{
	struct brnf_net *brnet = net_generic(net, brnf_net_id);

	return vlan_proto(skb) == htons(ETH_P_IPV6) &&
	       brnet->filter_vlan_tagged;
}