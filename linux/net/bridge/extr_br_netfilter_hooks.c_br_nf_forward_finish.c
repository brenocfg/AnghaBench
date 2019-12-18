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
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  dev; scalar_t__ cb; int /*<<< orphan*/  pkt_type; } ;
struct nf_bridge_info {int pkt_otherhost; struct net_device* physindev; int /*<<< orphan*/  frag_max_size; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  frag_max_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  frag_max_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 TYPE_2__* IP6CB (struct sk_buff*) ; 
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IS_ARP (struct sk_buff*) ; 
 int /*<<< orphan*/  NF_BR_FORWARD ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  br_forward_finish ; 
 int /*<<< orphan*/  br_nf_hook_thresh (int /*<<< orphan*/ ,struct net*,struct sock*,struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_vlan_arp (struct sk_buff*,struct net*) ; 
 struct nf_bridge_info* nf_bridge_info_get (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_push_encap_header (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_update_protocol (struct sk_buff*) ; 

__attribute__((used)) static int br_nf_forward_finish(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);
	struct net_device *in;

	if (!IS_ARP(skb) && !is_vlan_arp(skb, net)) {

		if (skb->protocol == htons(ETH_P_IP))
			nf_bridge->frag_max_size = IPCB(skb)->frag_max_size;

		if (skb->protocol == htons(ETH_P_IPV6))
			nf_bridge->frag_max_size = IP6CB(skb)->frag_max_size;

		in = nf_bridge->physindev;
		if (nf_bridge->pkt_otherhost) {
			skb->pkt_type = PACKET_OTHERHOST;
			nf_bridge->pkt_otherhost = false;
		}
		nf_bridge_update_protocol(skb);
	} else {
		in = *((struct net_device **)(skb->cb));
	}
	nf_bridge_push_encap_header(skb);

	br_nf_hook_thresh(NF_BR_FORWARD, net, sk, skb, in, skb->dev,
			  br_forward_finish);
	return 0;
}