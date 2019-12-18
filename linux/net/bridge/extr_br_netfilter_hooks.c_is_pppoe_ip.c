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
struct sk_buff {scalar_t__ protocol; } ;
struct net {int dummy; } ;
struct brnf_net {scalar_t__ filter_pppoe_tagged; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_PPP_SES ; 
 int /*<<< orphan*/  PPP_IP ; 
 int /*<<< orphan*/  brnf_net_id ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct brnf_net* net_generic (struct net const*,int /*<<< orphan*/ ) ; 
 scalar_t__ pppoe_proto (struct sk_buff const*) ; 

__attribute__((used)) static inline bool is_pppoe_ip(const struct sk_buff *skb, const struct net *net)
{
	struct brnf_net *brnet = net_generic(net, brnf_net_id);

	return skb->protocol == htons(ETH_P_PPP_SES) &&
	       pppoe_proto(skb) == htons(PPP_IP) && brnet->filter_pppoe_tagged;
}