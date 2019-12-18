#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int transport_header; scalar_t__ ip_summed; int /*<<< orphan*/  dev; scalar_t__ encapsulation; } ;
struct TYPE_9__ {TYPE_1__* devconf_all; } ;
struct net {TYPE_2__ ipv6; } ;
struct ipv6hdr {int dummy; } ;
struct ipv6_sr_hdr {int segments_left; scalar_t__ nexthdr; int hdrlen; struct in6_addr* segments; } ;
struct inet6_skb_parm {int srcrt; int lastopt; scalar_t__* nhoff; } ;
struct TYPE_10__ {int seg6_enabled; } ;
struct inet6_dev {TYPE_3__ cnf; } ;
struct in6_addr {int dummy; } ;
struct TYPE_13__ {int hop_limit; struct in6_addr daddr; } ;
struct TYPE_12__ {TYPE_4__* dev; scalar_t__ error; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_8__ {int seg6_enabled; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ICMPV6_EXC_HOPLIMIT ; 
 int /*<<< orphan*/  ICMPV6_HDR_FIELD ; 
 int /*<<< orphan*/  ICMPV6_TIME_EXCEED ; 
 int IFF_LOOPBACK ; 
 struct inet6_skb_parm* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSTATS_MIB_INHDRERRORS ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 scalar_t__ NEXTHDR_IPV6 ; 
 int /*<<< orphan*/  __IP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 struct inet6_dev* __in6_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_tunnel_rx (struct sk_buff*,int /*<<< orphan*/ ,struct net*) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_input (struct sk_buff*) ; 
 int /*<<< orphan*/  icmpv6_param_prob (struct sk_buff*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet6_dev* ip6_dst_idev (TYPE_5__*) ; 
 int /*<<< orphan*/  ip6_route_input (struct sk_buff*) ; 
 TYPE_6__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  seg6_hmac_validate_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  seg6_update_csum (struct sk_buff*) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 TYPE_5__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int skb_network_header (struct sk_buff*) ; 
 int skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int ipv6_srh_rcv(struct sk_buff *skb)
{
	struct inet6_skb_parm *opt = IP6CB(skb);
	struct net *net = dev_net(skb->dev);
	struct ipv6_sr_hdr *hdr;
	struct inet6_dev *idev;
	struct in6_addr *addr;
	int accept_seg6;

	hdr = (struct ipv6_sr_hdr *)skb_transport_header(skb);

	idev = __in6_dev_get(skb->dev);

	accept_seg6 = net->ipv6.devconf_all->seg6_enabled;
	if (accept_seg6 > idev->cnf.seg6_enabled)
		accept_seg6 = idev->cnf.seg6_enabled;

	if (!accept_seg6) {
		kfree_skb(skb);
		return -1;
	}

#ifdef CONFIG_IPV6_SEG6_HMAC
	if (!seg6_hmac_validate_skb(skb)) {
		kfree_skb(skb);
		return -1;
	}
#endif

looped_back:
	if (hdr->segments_left == 0) {
		if (hdr->nexthdr == NEXTHDR_IPV6) {
			int offset = (hdr->hdrlen + 1) << 3;

			skb_postpull_rcsum(skb, skb_network_header(skb),
					   skb_network_header_len(skb));

			if (!pskb_pull(skb, offset)) {
				kfree_skb(skb);
				return -1;
			}
			skb_postpull_rcsum(skb, skb_transport_header(skb),
					   offset);

			skb_reset_network_header(skb);
			skb_reset_transport_header(skb);
			skb->encapsulation = 0;

			__skb_tunnel_rx(skb, skb->dev, net);

			netif_rx(skb);
			return -1;
		}

		opt->srcrt = skb_network_header_len(skb);
		opt->lastopt = opt->srcrt;
		skb->transport_header += (hdr->hdrlen + 1) << 3;
		opt->nhoff = (&hdr->nexthdr) - skb_network_header(skb);

		return 1;
	}

	if (hdr->segments_left >= (hdr->hdrlen >> 1)) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_FIELD,
				  ((&hdr->segments_left) -
				   skb_network_header(skb)));
		return -1;
	}

	if (skb_cloned(skb)) {
		if (pskb_expand_head(skb, 0, 0, GFP_ATOMIC)) {
			__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
					IPSTATS_MIB_OUTDISCARDS);
			kfree_skb(skb);
			return -1;
		}
	}

	hdr = (struct ipv6_sr_hdr *)skb_transport_header(skb);

	hdr->segments_left--;
	addr = hdr->segments + hdr->segments_left;

	skb_push(skb, sizeof(struct ipv6hdr));

	if (skb->ip_summed == CHECKSUM_COMPLETE)
		seg6_update_csum(skb);

	ipv6_hdr(skb)->daddr = *addr;

	skb_dst_drop(skb);

	ip6_route_input(skb);

	if (skb_dst(skb)->error) {
		dst_input(skb);
		return -1;
	}

	if (skb_dst(skb)->dev->flags & IFF_LOOPBACK) {
		if (ipv6_hdr(skb)->hop_limit <= 1) {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
			icmpv6_send(skb, ICMPV6_TIME_EXCEED,
				    ICMPV6_EXC_HOPLIMIT, 0);
			kfree_skb(skb);
			return -1;
		}
		ipv6_hdr(skb)->hop_limit--;

		skb_pull(skb, sizeof(struct ipv6hdr));
		goto looped_back;
	}

	dst_input(skb);

	return -1;
}