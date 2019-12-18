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
struct tcphdr {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sysctl_ip_default_ttl; } ;
struct net {TYPE_1__ ipv4; } ;
struct iphdr {int /*<<< orphan*/  tot_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ LL_MAX_HEADER ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_forward (int /*<<< orphan*/ ,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  br_port_get_rcu (struct net_device const*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 struct tcphdr* nf_reject_ip_tcphdr_get (struct sk_buff*,struct tcphdr*,int) ; 
 int /*<<< orphan*/  nf_reject_ip_tcphdr_put (struct sk_buff*,struct sk_buff*,struct tcphdr const*) ; 
 struct iphdr* nf_reject_iphdr_put (struct sk_buff*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_bridge_iphdr_validate (struct sk_buff*) ; 
 int /*<<< orphan*/  nft_reject_br_push_etherhdr (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void nft_reject_br_send_v4_tcp_reset(struct net *net,
					    struct sk_buff *oldskb,
					    const struct net_device *dev,
					    int hook)
{
	struct sk_buff *nskb;
	struct iphdr *niph;
	const struct tcphdr *oth;
	struct tcphdr _oth;

	if (!nft_bridge_iphdr_validate(oldskb))
		return;

	oth = nf_reject_ip_tcphdr_get(oldskb, &_oth, hook);
	if (!oth)
		return;

	nskb = alloc_skb(sizeof(struct iphdr) + sizeof(struct tcphdr) +
			 LL_MAX_HEADER, GFP_ATOMIC);
	if (!nskb)
		return;

	skb_reserve(nskb, LL_MAX_HEADER);
	niph = nf_reject_iphdr_put(nskb, oldskb, IPPROTO_TCP,
				   net->ipv4.sysctl_ip_default_ttl);
	nf_reject_ip_tcphdr_put(nskb, oldskb, oth);
	niph->tot_len = htons(nskb->len);
	ip_send_check(niph);

	nft_reject_br_push_etherhdr(oldskb, nskb);

	br_forward(br_port_get_rcu(dev), nskb, false, true);
}