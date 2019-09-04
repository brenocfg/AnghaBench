#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct sk_buff {scalar_t__ ip_summed; TYPE_3__* dev; } ;
struct rtable {int dummy; } ;
struct in6_addr {int dummy; } ;
struct rt6_info {struct in6_addr rt6i_gateway; } ;
struct TYPE_17__ {int /*<<< orphan*/  addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  ipv6_addr; TYPE_4__ ipv4; } ;
struct TYPE_20__ {unsigned int length; int /*<<< orphan*/  flags; TYPE_5__ next_hop; int /*<<< orphan*/  ext_flags; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  id; } ;
struct TYPE_21__ {TYPE_7__ l3; } ;
struct qeth_hdr {TYPE_8__ hdr; } ;
struct TYPE_19__ {scalar_t__ type; } ;
struct TYPE_15__ {int /*<<< orphan*/  tx_csum; } ;
struct TYPE_14__ {scalar_t__ performance_stats; } ;
struct qeth_card {TYPE_6__ info; TYPE_2__ perf_stats; TYPE_1__ options; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_22__ {struct in6_addr daddr; } ;
struct TYPE_16__ {int /*<<< orphan*/  broadcast; } ;
struct TYPE_13__ {int /*<<< orphan*/  h_dest; } ;
struct TYPE_12__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 int /*<<< orphan*/  QETH_CAST_BROADCAST ; 
 int /*<<< orphan*/  QETH_CAST_MULTICAST ; 
 int /*<<< orphan*/  QETH_CAST_UNICAST ; 
 int /*<<< orphan*/  QETH_HDR_EXT_INCLUDE_VLAN_TAG ; 
 int /*<<< orphan*/  QETH_HDR_EXT_VLAN_FRAME ; 
 int /*<<< orphan*/  QETH_HDR_IPV6 ; 
 int /*<<< orphan*/  QETH_HDR_PASSTHRU ; 
 int /*<<< orphan*/  QETH_HEADER_TYPE_LAYER3 ; 
 int RTN_MULTICAST ; 
 TYPE_11__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ ether_addr_equal_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_any (struct in6_addr*) ; 
 TYPE_9__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct in6_addr const*,int) ; 
 int /*<<< orphan*/  memset (struct qeth_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qeth_l3_cast_type_to_flag (int) ; 
 int /*<<< orphan*/  qeth_tx_csum (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rt_nexthop (struct rtable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 struct rt6_info* skb_rt6_info (struct sk_buff*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

__attribute__((used)) static void qeth_l3_fill_header(struct qeth_card *card, struct qeth_hdr *hdr,
				struct sk_buff *skb, int ipv, int cast_type,
				unsigned int data_len)
{
	memset(hdr, 0, sizeof(struct qeth_hdr));
	hdr->hdr.l3.id = QETH_HEADER_TYPE_LAYER3;
	hdr->hdr.l3.length = data_len;

	/*
	 * before we're going to overwrite this location with next hop ip.
	 * v6 uses passthrough, v4 sets the tag in the QDIO header.
	 */
	if (skb_vlan_tag_present(skb)) {
		if ((ipv == 4) || (card->info.type == QETH_CARD_TYPE_IQD))
			hdr->hdr.l3.ext_flags = QETH_HDR_EXT_VLAN_FRAME;
		else
			hdr->hdr.l3.ext_flags = QETH_HDR_EXT_INCLUDE_VLAN_TAG;
		hdr->hdr.l3.vlan_id = skb_vlan_tag_get(skb);
	}

	if (!skb_is_gso(skb) && skb->ip_summed == CHECKSUM_PARTIAL) {
		qeth_tx_csum(skb, &hdr->hdr.l3.ext_flags, ipv);
		if (card->options.performance_stats)
			card->perf_stats.tx_csum++;
	}

	/* OSA only: */
	if (!ipv) {
		hdr->hdr.l3.flags = QETH_HDR_PASSTHRU;
		if (ether_addr_equal_64bits(eth_hdr(skb)->h_dest,
					    skb->dev->broadcast))
			hdr->hdr.l3.flags |= QETH_CAST_BROADCAST;
		else
			hdr->hdr.l3.flags |= (cast_type == RTN_MULTICAST) ?
				QETH_CAST_MULTICAST : QETH_CAST_UNICAST;
		return;
	}

	hdr->hdr.l3.flags = qeth_l3_cast_type_to_flag(cast_type);
	rcu_read_lock();
	if (ipv == 4) {
		struct rtable *rt = skb_rtable(skb);

		*((__be32 *) &hdr->hdr.l3.next_hop.ipv4.addr) = (rt) ?
				rt_nexthop(rt, ip_hdr(skb)->daddr) :
				ip_hdr(skb)->daddr;
	} else {
		/* IPv6 */
		const struct rt6_info *rt = skb_rt6_info(skb);
		const struct in6_addr *next_hop;

		if (rt && !ipv6_addr_any(&rt->rt6i_gateway))
			next_hop = &rt->rt6i_gateway;
		else
			next_hop = &ipv6_hdr(skb)->daddr;
		memcpy(hdr->hdr.l3.next_hop.ipv6_addr, next_hop, 16);

		hdr->hdr.l3.flags |= QETH_HDR_IPV6;
		if (card->info.type != QETH_CARD_TYPE_IQD)
			hdr->hdr.l3.flags |= QETH_HDR_PASSTHRU;
	}
	rcu_read_unlock();
}