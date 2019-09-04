#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ mark; } ;
struct nft_pktinfo {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  net; } ;
struct iphdr {scalar_t__ saddr; scalar_t__ daddr; scalar_t__ tos; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 unsigned int NF_DROP ; 
 unsigned int NF_DROP_ERR (int) ; 
 unsigned int NF_STOLEN ; 
 int /*<<< orphan*/  RTN_UNSPEC ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_route_me_harder (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned int nft_do_chain (struct nft_pktinfo*,void*) ; 
 int /*<<< orphan*/  nft_set_pktinfo (struct nft_pktinfo*,struct sk_buff*,struct nf_hook_state const*) ; 
 int /*<<< orphan*/  nft_set_pktinfo_ipv4 (struct nft_pktinfo*,struct sk_buff*) ; 

__attribute__((used)) static unsigned int nf_route_table_hook(void *priv,
					struct sk_buff *skb,
					const struct nf_hook_state *state)
{
	unsigned int ret;
	struct nft_pktinfo pkt;
	u32 mark;
	__be32 saddr, daddr;
	u_int8_t tos;
	const struct iphdr *iph;
	int err;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_ipv4(&pkt, skb);

	mark = skb->mark;
	iph = ip_hdr(skb);
	saddr = iph->saddr;
	daddr = iph->daddr;
	tos = iph->tos;

	ret = nft_do_chain(&pkt, priv);
	if (ret != NF_DROP && ret != NF_STOLEN) {
		iph = ip_hdr(skb);

		if (iph->saddr != saddr ||
		    iph->daddr != daddr ||
		    skb->mark != mark ||
		    iph->tos != tos) {
			err = ip_route_me_harder(state->net, skb, RTN_UNSPEC);
			if (err < 0)
				ret = NF_DROP_ERR(err);
		}
	}
	return ret;
}