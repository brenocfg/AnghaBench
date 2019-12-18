#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
struct sk_buff {scalar_t__ pkt_type; void* protocol; int /*<<< orphan*/  dev; } ;
struct nf_hook_state {int /*<<< orphan*/  net; int /*<<< orphan*/  in; int /*<<< orphan*/  out; } ;
struct nf_bridge_info {int pkt_otherhost; int /*<<< orphan*/  physoutdev; int /*<<< orphan*/  frag_max_size; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  frag_max_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  frag_max_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 TYPE_2__* IP6CB (struct sk_buff*) ; 
 TYPE_1__* IPCB (struct sk_buff*) ; 
 scalar_t__ IS_IP (struct sk_buff*) ; 
 scalar_t__ IS_IPV6 (struct sk_buff*) ; 
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ NFPROTO_IPV6 ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  NF_HOOK (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_FORWARD ; 
 unsigned int NF_STOLEN ; 
 scalar_t__ PACKET_HOST ; 
 scalar_t__ PACKET_OTHERHOST ; 
 int /*<<< orphan*/  br_nf_forward_finish ; 
 scalar_t__ br_validate_ipv4 (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ br_validate_ipv6 (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct net_device* bridge_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brnf_get_logical_dev (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 scalar_t__ is_pppoe_ip (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_pppoe_ipv6 (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_vlan_ip (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_vlan_ipv6 (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct nf_bridge_info* nf_bridge_info_get (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_pull_encap_header (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_unshare (struct sk_buff*) ; 

__attribute__((used)) static unsigned int br_nf_forward_ip(void *priv,
				     struct sk_buff *skb,
				     const struct nf_hook_state *state)
{
	struct nf_bridge_info *nf_bridge;
	struct net_device *parent;
	u_int8_t pf;

	nf_bridge = nf_bridge_info_get(skb);
	if (!nf_bridge)
		return NF_ACCEPT;

	/* Need exclusive nf_bridge_info since we might have multiple
	 * different physoutdevs. */
	if (!nf_bridge_unshare(skb))
		return NF_DROP;

	nf_bridge = nf_bridge_info_get(skb);
	if (!nf_bridge)
		return NF_DROP;

	parent = bridge_parent(state->out);
	if (!parent)
		return NF_DROP;

	if (IS_IP(skb) || is_vlan_ip(skb, state->net) ||
	    is_pppoe_ip(skb, state->net))
		pf = NFPROTO_IPV4;
	else if (IS_IPV6(skb) || is_vlan_ipv6(skb, state->net) ||
		 is_pppoe_ipv6(skb, state->net))
		pf = NFPROTO_IPV6;
	else
		return NF_ACCEPT;

	nf_bridge_pull_encap_header(skb);

	if (skb->pkt_type == PACKET_OTHERHOST) {
		skb->pkt_type = PACKET_HOST;
		nf_bridge->pkt_otherhost = true;
	}

	if (pf == NFPROTO_IPV4) {
		if (br_validate_ipv4(state->net, skb))
			return NF_DROP;
		IPCB(skb)->frag_max_size = nf_bridge->frag_max_size;
	}

	if (pf == NFPROTO_IPV6) {
		if (br_validate_ipv6(state->net, skb))
			return NF_DROP;
		IP6CB(skb)->frag_max_size = nf_bridge->frag_max_size;
	}

	nf_bridge->physoutdev = skb->dev;
	if (pf == NFPROTO_IPV4)
		skb->protocol = htons(ETH_P_IP);
	else
		skb->protocol = htons(ETH_P_IPV6);

	NF_HOOK(pf, NF_INET_FORWARD, state->net, NULL, skb,
		brnf_get_logical_dev(skb, state->in, state->net),
		parent,	br_nf_forward_finish);

	return NF_STOLEN;
}