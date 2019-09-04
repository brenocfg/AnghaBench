#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  pkt_type; } ;
struct TYPE_6__ {struct net_device* dev; } ;
struct rtable {TYPE_1__ dst; } ;
struct nf_bridge_info {int pkt_otherhost; struct net_device* physindev; scalar_t__ in_prerouting; int /*<<< orphan*/  frag_max_size; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  tos; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct in_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  frag_max_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  h_dest; } ;
struct TYPE_7__ {struct net_device* dev; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 scalar_t__ IN_DEV_FORWARD (struct in_device*) ; 
 TYPE_5__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  NF_BR_PRE_ROUTING ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  br_handle_frame_finish ; 
 int /*<<< orphan*/  br_nf_hook_thresh (int /*<<< orphan*/ ,struct net*,struct sock*,struct sk_buff*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ br_nf_ipv4_daddr_was_changed (struct sk_buff*,struct nf_bridge_info*) ; 
 int /*<<< orphan*/  br_nf_pre_routing_finish_bridge ; 
 struct rtable* bridge_parent_rtable (struct net_device*) ; 
 TYPE_4__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_route_input (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 struct rtable* ip_route_output (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nf_bridge_info* nf_bridge_info_get (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_push_encap_header (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_update_protocol (struct sk_buff*) ; 
 TYPE_3__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_1__*) ; 
 int /*<<< orphan*/  skb_dst_set_noref (struct sk_buff*,TYPE_1__*) ; 

__attribute__((used)) static int br_nf_pre_routing_finish(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	struct iphdr *iph = ip_hdr(skb);
	struct nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);
	struct rtable *rt;
	int err;

	nf_bridge->frag_max_size = IPCB(skb)->frag_max_size;

	if (nf_bridge->pkt_otherhost) {
		skb->pkt_type = PACKET_OTHERHOST;
		nf_bridge->pkt_otherhost = false;
	}
	nf_bridge->in_prerouting = 0;
	if (br_nf_ipv4_daddr_was_changed(skb, nf_bridge)) {
		if ((err = ip_route_input(skb, iph->daddr, iph->saddr, iph->tos, dev))) {
			struct in_device *in_dev = __in_dev_get_rcu(dev);

			/* If err equals -EHOSTUNREACH the error is due to a
			 * martian destination or due to the fact that
			 * forwarding is disabled. For most martian packets,
			 * ip_route_output_key() will fail. It won't fail for 2 types of
			 * martian destinations: loopback destinations and destination
			 * 0.0.0.0. In both cases the packet will be dropped because the
			 * destination is the loopback device and not the bridge. */
			if (err != -EHOSTUNREACH || !in_dev || IN_DEV_FORWARD(in_dev))
				goto free_skb;

			rt = ip_route_output(net, iph->daddr, 0,
					     RT_TOS(iph->tos), 0);
			if (!IS_ERR(rt)) {
				/* - Bridged-and-DNAT'ed traffic doesn't
				 *   require ip_forwarding. */
				if (rt->dst.dev == dev) {
					skb_dst_set(skb, &rt->dst);
					goto bridged_dnat;
				}
				ip_rt_put(rt);
			}
free_skb:
			kfree_skb(skb);
			return 0;
		} else {
			if (skb_dst(skb)->dev == dev) {
bridged_dnat:
				skb->dev = nf_bridge->physindev;
				nf_bridge_update_protocol(skb);
				nf_bridge_push_encap_header(skb);
				br_nf_hook_thresh(NF_BR_PRE_ROUTING,
						  net, sk, skb, skb->dev,
						  NULL,
						  br_nf_pre_routing_finish_bridge);
				return 0;
			}
			ether_addr_copy(eth_hdr(skb)->h_dest, dev->dev_addr);
			skb->pkt_type = PACKET_HOST;
		}
	} else {
		rt = bridge_parent_rtable(nf_bridge->physindev);
		if (!rt) {
			kfree_skb(skb);
			return 0;
		}
		skb_dst_set_noref(skb, &rt->dst);
	}

	skb->dev = nf_bridge->physindev;
	nf_bridge_update_protocol(skb);
	nf_bridge_push_encap_header(skb);
	br_nf_hook_thresh(NF_BR_PRE_ROUTING, net, sk, skb, skb->dev, NULL,
			  br_handle_frame_finish);
	return 0;
}