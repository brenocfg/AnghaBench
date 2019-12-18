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
struct tcphdr {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* devconf_all; } ;
struct net {TYPE_2__ ipv6; } ;
struct ipv6hdr {int /*<<< orphan*/  payload_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  hop_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ LL_MAX_HEADER ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_forward (int /*<<< orphan*/ ,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  br_port_get_rcu (struct net_device const*) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 struct tcphdr* nf_reject_ip6_tcphdr_get (struct sk_buff*,struct tcphdr*,unsigned int*,int) ; 
 int /*<<< orphan*/  nf_reject_ip6_tcphdr_put (struct sk_buff*,struct sk_buff*,struct tcphdr const*,unsigned int) ; 
 struct ipv6hdr* nf_reject_ip6hdr_put (struct sk_buff*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_bridge_ip6hdr_validate (struct sk_buff*) ; 
 int /*<<< orphan*/  nft_reject_br_push_etherhdr (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void nft_reject_br_send_v6_tcp_reset(struct net *net,
					    struct sk_buff *oldskb,
					    const struct net_device *dev,
					    int hook)
{
	struct sk_buff *nskb;
	const struct tcphdr *oth;
	struct tcphdr _oth;
	unsigned int otcplen;
	struct ipv6hdr *nip6h;

	if (!nft_bridge_ip6hdr_validate(oldskb))
		return;

	oth = nf_reject_ip6_tcphdr_get(oldskb, &_oth, &otcplen, hook);
	if (!oth)
		return;

	nskb = alloc_skb(sizeof(struct ipv6hdr) + sizeof(struct tcphdr) +
			 LL_MAX_HEADER, GFP_ATOMIC);
	if (!nskb)
		return;

	skb_reserve(nskb, LL_MAX_HEADER);
	nip6h = nf_reject_ip6hdr_put(nskb, oldskb, IPPROTO_TCP,
				     net->ipv6.devconf_all->hop_limit);
	nf_reject_ip6_tcphdr_put(nskb, oldskb, oth, otcplen);
	nip6h->payload_len = htons(nskb->len - sizeof(struct ipv6hdr));

	nft_reject_br_push_etherhdr(oldskb, nskb);

	br_forward(br_port_get_rcu(dev), nskb, false, true);
}