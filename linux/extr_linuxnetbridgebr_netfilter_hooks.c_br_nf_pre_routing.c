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
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  nf_bridge; } ;
struct nf_hook_state {int /*<<< orphan*/  sk; int /*<<< orphan*/  net; int /*<<< orphan*/  in; } ;
struct nf_bridge_info {int /*<<< orphan*/  ipv4_daddr; } ;
struct net_bridge_port {struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  nf_call_iptables; int /*<<< orphan*/  nf_call_ip6tables; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  IS_IP (struct sk_buff*) ; 
 scalar_t__ IS_IPV6 (struct sk_buff*) ; 
 int /*<<< orphan*/  IS_PPPOE_IP (struct sk_buff*) ; 
 scalar_t__ IS_PPPOE_IPV6 (struct sk_buff*) ; 
 int /*<<< orphan*/  IS_VLAN_IP (struct sk_buff*) ; 
 scalar_t__ IS_VLAN_IPV6 (struct sk_buff*) ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_PRE_ROUTING ; 
 unsigned int NF_STOLEN ; 
 int /*<<< orphan*/  br_nf_pre_routing_finish ; 
 unsigned int br_nf_pre_routing_ipv6 (void*,struct sk_buff*,struct nf_hook_state const*) ; 
 struct net_bridge_port* br_port_get_rcu (int /*<<< orphan*/ ) ; 
 scalar_t__ br_validate_ipv4 (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  brnf_call_ip6tables ; 
 int /*<<< orphan*/  brnf_call_iptables ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_alloc (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_encap_header_len (struct sk_buff*) ; 
 struct nf_bridge_info* nf_bridge_info_get (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_pull_encap_header_rcsum (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_pre_routing (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int br_nf_pre_routing(void *priv,
				      struct sk_buff *skb,
				      const struct nf_hook_state *state)
{
	struct nf_bridge_info *nf_bridge;
	struct net_bridge_port *p;
	struct net_bridge *br;
	__u32 len = nf_bridge_encap_header_len(skb);

	if (unlikely(!pskb_may_pull(skb, len)))
		return NF_DROP;

	p = br_port_get_rcu(state->in);
	if (p == NULL)
		return NF_DROP;
	br = p->br;

	if (IS_IPV6(skb) || IS_VLAN_IPV6(skb) || IS_PPPOE_IPV6(skb)) {
		if (!brnf_call_ip6tables && !br->nf_call_ip6tables)
			return NF_ACCEPT;

		nf_bridge_pull_encap_header_rcsum(skb);
		return br_nf_pre_routing_ipv6(priv, skb, state);
	}

	if (!brnf_call_iptables && !br->nf_call_iptables)
		return NF_ACCEPT;

	if (!IS_IP(skb) && !IS_VLAN_IP(skb) && !IS_PPPOE_IP(skb))
		return NF_ACCEPT;

	nf_bridge_pull_encap_header_rcsum(skb);

	if (br_validate_ipv4(state->net, skb))
		return NF_DROP;

	nf_bridge_put(skb->nf_bridge);
	if (!nf_bridge_alloc(skb))
		return NF_DROP;
	if (!setup_pre_routing(skb))
		return NF_DROP;

	nf_bridge = nf_bridge_info_get(skb);
	nf_bridge->ipv4_daddr = ip_hdr(skb)->daddr;

	skb->protocol = htons(ETH_P_IP);

	NF_HOOK(NFPROTO_IPV4, NF_INET_PRE_ROUTING, state->net, state->sk, skb,
		skb->dev, NULL,
		br_nf_pre_routing_finish);

	return NF_STOLEN;
}