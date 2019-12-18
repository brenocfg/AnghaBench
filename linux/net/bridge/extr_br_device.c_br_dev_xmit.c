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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ protocol; scalar_t__ len; } ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct nf_br_ops {scalar_t__ (* br_dev_xmit_hook ) (struct sk_buff*) ;} ;
struct net_device {int dummy; } ;
struct net_bridge_mdb_entry {int dummy; } ;
struct net_bridge_fdb_entry {int /*<<< orphan*/  dst; } ;
struct net_bridge {int /*<<< orphan*/  stats; } ;
struct nd_msg {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct ethhdr {scalar_t__ h_proto; unsigned char* h_dest; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {scalar_t__ frag_max_size; struct net_device* brdev; } ;
struct TYPE_3__ {scalar_t__ nexthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_NEIGH_SUPPRESS_ENABLED ; 
 TYPE_2__* BR_INPUT_SKB_CB (struct sk_buff*) ; 
 scalar_t__ BR_INPUT_SKB_CB_MROUTERS_ONLY (struct sk_buff*) ; 
 int /*<<< orphan*/  BR_PKT_BROADCAST ; 
 int /*<<< orphan*/  BR_PKT_MULTICAST ; 
 int /*<<< orphan*/  BR_PKT_UNICAST ; 
 int /*<<< orphan*/  CONFIG_INET ; 
 int /*<<< orphan*/  CONFIG_IPV6 ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ETH_P_RARP ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  br_allowed_ingress (struct net_bridge*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_do_proxy_suppress_arp (struct sk_buff*,struct net_bridge*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_do_suppress_nd (struct sk_buff*,struct net_bridge*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nd_msg*) ; 
 struct net_bridge_fdb_entry* br_fdb_find_rcu (struct net_bridge*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_flood (struct net_bridge*,struct sk_buff*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  br_forward (int /*<<< orphan*/ ,struct sk_buff*,int,int) ; 
 struct nd_msg* br_is_nd_neigh_msg (struct sk_buff*,struct nd_msg*) ; 
 struct net_bridge_mdb_entry* br_mdb_get (struct net_bridge*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_multicast_flood (struct net_bridge_mdb_entry*,struct sk_buff*,int,int) ; 
 scalar_t__ br_multicast_querier_exists (struct net_bridge*,struct ethhdr*) ; 
 scalar_t__ br_multicast_rcv (struct net_bridge*,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ br_opt_get (struct net_bridge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_switchdev_frame_unmark (struct sk_buff*) ; 
 int /*<<< orphan*/  br_vlan_group_rcu (struct net_bridge*) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ is_broadcast_ether_addr (unsigned char const*) ; 
 scalar_t__ is_multicast_ether_addr (unsigned char const*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netpoll_tx_running (struct net_device*) ; 
 int /*<<< orphan*/  nf_br_ops ; 
 scalar_t__ pskb_may_pull (struct sk_buff*,int) ; 
 struct nf_br_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ stub1 (struct sk_buff*) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

netdev_tx_t br_dev_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct net_bridge *br = netdev_priv(dev);
	struct net_bridge_fdb_entry *dst;
	struct net_bridge_mdb_entry *mdst;
	struct pcpu_sw_netstats *brstats = this_cpu_ptr(br->stats);
	const struct nf_br_ops *nf_ops;
	const unsigned char *dest;
	struct ethhdr *eth;
	u16 vid = 0;

	rcu_read_lock();
	nf_ops = rcu_dereference(nf_br_ops);
	if (nf_ops && nf_ops->br_dev_xmit_hook(skb)) {
		rcu_read_unlock();
		return NETDEV_TX_OK;
	}

	u64_stats_update_begin(&brstats->syncp);
	brstats->tx_packets++;
	brstats->tx_bytes += skb->len;
	u64_stats_update_end(&brstats->syncp);

	br_switchdev_frame_unmark(skb);
	BR_INPUT_SKB_CB(skb)->brdev = dev;
	BR_INPUT_SKB_CB(skb)->frag_max_size = 0;

	skb_reset_mac_header(skb);
	eth = eth_hdr(skb);
	skb_pull(skb, ETH_HLEN);

	if (!br_allowed_ingress(br, br_vlan_group_rcu(br), skb, &vid))
		goto out;

	if (IS_ENABLED(CONFIG_INET) &&
	    (eth->h_proto == htons(ETH_P_ARP) ||
	     eth->h_proto == htons(ETH_P_RARP)) &&
	    br_opt_get(br, BROPT_NEIGH_SUPPRESS_ENABLED)) {
		br_do_proxy_suppress_arp(skb, br, vid, NULL);
	} else if (IS_ENABLED(CONFIG_IPV6) &&
		   skb->protocol == htons(ETH_P_IPV6) &&
		   br_opt_get(br, BROPT_NEIGH_SUPPRESS_ENABLED) &&
		   pskb_may_pull(skb, sizeof(struct ipv6hdr) +
				 sizeof(struct nd_msg)) &&
		   ipv6_hdr(skb)->nexthdr == IPPROTO_ICMPV6) {
			struct nd_msg *msg, _msg;

			msg = br_is_nd_neigh_msg(skb, &_msg);
			if (msg)
				br_do_suppress_nd(skb, br, vid, NULL, msg);
	}

	dest = eth_hdr(skb)->h_dest;
	if (is_broadcast_ether_addr(dest)) {
		br_flood(br, skb, BR_PKT_BROADCAST, false, true);
	} else if (is_multicast_ether_addr(dest)) {
		if (unlikely(netpoll_tx_running(dev))) {
			br_flood(br, skb, BR_PKT_MULTICAST, false, true);
			goto out;
		}
		if (br_multicast_rcv(br, NULL, skb, vid)) {
			kfree_skb(skb);
			goto out;
		}

		mdst = br_mdb_get(br, skb, vid);
		if ((mdst || BR_INPUT_SKB_CB_MROUTERS_ONLY(skb)) &&
		    br_multicast_querier_exists(br, eth_hdr(skb)))
			br_multicast_flood(mdst, skb, false, true);
		else
			br_flood(br, skb, BR_PKT_MULTICAST, false, true);
	} else if ((dst = br_fdb_find_rcu(br, dest, vid)) != NULL) {
		br_forward(dst->dst, skb, false, true);
	} else {
		br_flood(br, skb, BR_PKT_UNICAST, false, true);
	}
out:
	rcu_read_unlock();
	return NETDEV_TX_OK;
}