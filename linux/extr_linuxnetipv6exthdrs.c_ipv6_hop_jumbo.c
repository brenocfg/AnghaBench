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
typedef  scalar_t__ u32 ;
struct sk_buff {int len; int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct inet6_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {scalar_t__ payload_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_HDR_FIELD ; 
 TYPE_2__* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP6SKB_JUMBOGRAM ; 
 int /*<<< orphan*/  IPSTATS_MIB_INHDRERRORS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INTRUNCATEDPKTS ; 
 scalar_t__ IPV6_MAXPLEN ; 
 int /*<<< orphan*/  __IP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 struct inet6_dev* __in6_dev_get_safely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmpv6_param_prob (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 struct net* ipv6_skb_net (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,unsigned char const) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ pskb_trim_rcsum (struct sk_buff*,scalar_t__) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static bool ipv6_hop_jumbo(struct sk_buff *skb, int optoff)
{
	const unsigned char *nh = skb_network_header(skb);
	struct inet6_dev *idev = __in6_dev_get_safely(skb->dev);
	struct net *net = ipv6_skb_net(skb);
	u32 pkt_len;

	if (nh[optoff + 1] != 4 || (optoff & 3) != 2) {
		net_dbg_ratelimited("ipv6_hop_jumbo: wrong jumbo opt length/alignment %d\n",
				    nh[optoff+1]);
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		goto drop;
	}

	pkt_len = ntohl(*(__be32 *)(nh + optoff + 2));
	if (pkt_len <= IPV6_MAXPLEN) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_FIELD, optoff+2);
		return false;
	}
	if (ipv6_hdr(skb)->payload_len) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_FIELD, optoff);
		return false;
	}

	if (pkt_len > skb->len - sizeof(struct ipv6hdr)) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INTRUNCATEDPKTS);
		goto drop;
	}

	if (pskb_trim_rcsum(skb, pkt_len + sizeof(struct ipv6hdr)))
		goto drop;

	IP6CB(skb)->flags |= IP6SKB_JUMBOGRAM;
	return true;

drop:
	kfree_skb(skb);
	return false;
}