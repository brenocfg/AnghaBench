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
struct nf_hook_state {TYPE_1__* out; struct net* net; } ;
struct net {int dummy; } ;
struct clusterip_config {scalar_t__ ifindex; int /*<<< orphan*/  clustermac; } ;
struct arphdr {scalar_t__ ar_hrd; scalar_t__ ar_pro; int ar_pln; scalar_t__ ar_hln; scalar_t__ ar_op; } ;
struct arp_payload {int /*<<< orphan*/  src_hw; int /*<<< orphan*/  src_ip; } ;
struct TYPE_2__ {scalar_t__ ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ARPOP_REPLY ; 
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 unsigned int NF_ACCEPT ; 
 struct arphdr* arp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  arp_print (struct arp_payload*) ; 
 struct clusterip_config* clusterip_config_find_get (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterip_config_put (struct clusterip_config*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static unsigned int
arp_mangle(void *priv,
	   struct sk_buff *skb,
	   const struct nf_hook_state *state)
{
	struct arphdr *arp = arp_hdr(skb);
	struct arp_payload *payload;
	struct clusterip_config *c;
	struct net *net = state->net;

	/* we don't care about non-ethernet and non-ipv4 ARP */
	if (arp->ar_hrd != htons(ARPHRD_ETHER) ||
	    arp->ar_pro != htons(ETH_P_IP) ||
	    arp->ar_pln != 4 || arp->ar_hln != ETH_ALEN)
		return NF_ACCEPT;

	/* we only want to mangle arp requests and replies */
	if (arp->ar_op != htons(ARPOP_REPLY) &&
	    arp->ar_op != htons(ARPOP_REQUEST))
		return NF_ACCEPT;

	payload = (void *)(arp+1);

	/* if there is no clusterip configuration for the arp reply's
	 * source ip, we don't want to mangle it */
	c = clusterip_config_find_get(net, payload->src_ip, 0);
	if (!c)
		return NF_ACCEPT;

	/* normally the linux kernel always replies to arp queries of
	 * addresses on different interfacs.  However, in the CLUSTERIP case
	 * this wouldn't work, since we didn't subscribe the mcast group on
	 * other interfaces */
	if (c->ifindex != state->out->ifindex) {
		pr_debug("not mangling arp reply on different interface: cip'%d'-skb'%d'\n",
			 c->ifindex, state->out->ifindex);
		clusterip_config_put(c);
		return NF_ACCEPT;
	}

	/* mangle reply hardware address */
	memcpy(payload->src_hw, c->clustermac, arp->ar_hln);

#ifdef DEBUG
	pr_debug("mangled arp reply: ");
	arp_print(payload);
#endif

	clusterip_config_put(c);

	return NF_ACCEPT;
}