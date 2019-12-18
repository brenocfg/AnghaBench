#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int transport_header; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int max_hbh_opts_len; } ;
struct TYPE_7__ {TYPE_1__ sysctl; } ;
struct net {TYPE_2__ ipv6; } ;
struct ipv6hdr {int dummy; } ;
struct inet6_skb_parm {int nhoff; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_hbh_opts_cnt; } ;
struct TYPE_9__ {TYPE_3__ sysctl; } ;
struct TYPE_10__ {TYPE_4__ ipv6; } ;

/* Variables and functions */
 struct inet6_skb_parm* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP6SKB_HOPBYHOP ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 TYPE_5__ init_net ; 
 scalar_t__ ip6_parse_tlv (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int* skb_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  tlvprochopopt_lst ; 

int ipv6_parse_hopopts(struct sk_buff *skb)
{
	struct inet6_skb_parm *opt = IP6CB(skb);
	struct net *net = dev_net(skb->dev);
	int extlen;

	/*
	 * skb_network_header(skb) is equal to skb->data, and
	 * skb_network_header_len(skb) is always equal to
	 * sizeof(struct ipv6hdr) by definition of
	 * hop-by-hop options.
	 */
	if (!pskb_may_pull(skb, sizeof(struct ipv6hdr) + 8) ||
	    !pskb_may_pull(skb, (sizeof(struct ipv6hdr) +
				 ((skb_transport_header(skb)[1] + 1) << 3)))) {
fail_and_free:
		kfree_skb(skb);
		return -1;
	}

	extlen = (skb_transport_header(skb)[1] + 1) << 3;
	if (extlen > net->ipv6.sysctl.max_hbh_opts_len)
		goto fail_and_free;

	opt->flags |= IP6SKB_HOPBYHOP;
	if (ip6_parse_tlv(tlvprochopopt_lst, skb,
			  init_net.ipv6.sysctl.max_hbh_opts_cnt)) {
		skb->transport_header += extlen;
		opt = IP6CB(skb);
		opt->nhoff = sizeof(struct ipv6hdr);
		return 1;
	}
	return -1;
}