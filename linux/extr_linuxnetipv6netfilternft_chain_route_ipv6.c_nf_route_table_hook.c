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
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ mark; } ;
struct nft_pktinfo {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  net; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  saddr ;
typedef  int /*<<< orphan*/  daddr ;
struct TYPE_2__ {scalar_t__ hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 unsigned int NF_DROP ; 
 unsigned int NF_DROP_ERR (int) ; 
 unsigned int NF_STOLEN ; 
 int ip6_route_me_harder (int /*<<< orphan*/ ,struct sk_buff*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,int /*<<< orphan*/ *,int) ; 
 unsigned int nft_do_chain (struct nft_pktinfo*,void*) ; 
 int /*<<< orphan*/  nft_set_pktinfo (struct nft_pktinfo*,struct sk_buff*,struct nf_hook_state const*) ; 
 int /*<<< orphan*/  nft_set_pktinfo_ipv6 (struct nft_pktinfo*,struct sk_buff*) ; 

__attribute__((used)) static unsigned int nf_route_table_hook(void *priv,
					struct sk_buff *skb,
					const struct nf_hook_state *state)
{
	unsigned int ret;
	struct nft_pktinfo pkt;
	struct in6_addr saddr, daddr;
	u_int8_t hop_limit;
	u32 mark, flowlabel;
	int err;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_ipv6(&pkt, skb);

	/* save source/dest address, mark, hoplimit, flowlabel, priority */
	memcpy(&saddr, &ipv6_hdr(skb)->saddr, sizeof(saddr));
	memcpy(&daddr, &ipv6_hdr(skb)->daddr, sizeof(daddr));
	mark = skb->mark;
	hop_limit = ipv6_hdr(skb)->hop_limit;

	/* flowlabel and prio (includes version, which shouldn't change either */
	flowlabel = *((u32 *)ipv6_hdr(skb));

	ret = nft_do_chain(&pkt, priv);
	if (ret != NF_DROP && ret != NF_STOLEN &&
	    (memcmp(&ipv6_hdr(skb)->saddr, &saddr, sizeof(saddr)) ||
	     memcmp(&ipv6_hdr(skb)->daddr, &daddr, sizeof(daddr)) ||
	     skb->mark != mark ||
	     ipv6_hdr(skb)->hop_limit != hop_limit ||
	     flowlabel != *((u_int32_t *)ipv6_hdr(skb)))) {
		err = ip6_route_me_harder(state->net, skb);
		if (err < 0)
			ret = NF_DROP_ERR(err);
	}

	return ret;
}