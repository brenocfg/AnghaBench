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
struct sk_buff {scalar_t__ cb; } ;
struct nf_hook_state {int /*<<< orphan*/  out; struct net_device* in; int /*<<< orphan*/  sk; int /*<<< orphan*/  net; } ;
struct net_device {int dummy; } ;
struct net_bridge_port {struct net_bridge* br; } ;
struct net_bridge {int dummy; } ;
struct brnf_net {int /*<<< orphan*/  call_arptables; } ;
struct TYPE_2__ {int ar_pln; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_NF_CALL_ARPTABLES ; 
 int /*<<< orphan*/  IS_ARP (struct sk_buff*) ; 
 int /*<<< orphan*/  NFPROTO_ARP ; 
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_ARP_FORWARD ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int NF_STOLEN ; 
 TYPE_1__* arp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  br_nf_forward_finish ; 
 int /*<<< orphan*/  br_opt_get (struct net_bridge*,int /*<<< orphan*/ ) ; 
 struct net_bridge_port* br_port_get_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brnf_net_id ; 
 scalar_t__ is_vlan_arp (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct brnf_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_bridge_pull_encap_header (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_push_encap_header (struct sk_buff*) ; 

__attribute__((used)) static unsigned int br_nf_forward_arp(void *priv,
				      struct sk_buff *skb,
				      const struct nf_hook_state *state)
{
	struct net_bridge_port *p;
	struct net_bridge *br;
	struct net_device **d = (struct net_device **)(skb->cb);
	struct brnf_net *brnet;

	p = br_port_get_rcu(state->out);
	if (p == NULL)
		return NF_ACCEPT;
	br = p->br;

	brnet = net_generic(state->net, brnf_net_id);
	if (!brnet->call_arptables && !br_opt_get(br, BROPT_NF_CALL_ARPTABLES))
		return NF_ACCEPT;

	if (!IS_ARP(skb)) {
		if (!is_vlan_arp(skb, state->net))
			return NF_ACCEPT;
		nf_bridge_pull_encap_header(skb);
	}

	if (arp_hdr(skb)->ar_pln != 4) {
		if (is_vlan_arp(skb, state->net))
			nf_bridge_push_encap_header(skb);
		return NF_ACCEPT;
	}
	*d = state->in;
	NF_HOOK(NFPROTO_ARP, NF_ARP_FORWARD, state->net, state->sk, skb,
		state->in, state->out, br_nf_forward_finish);

	return NF_STOLEN;
}