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
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct sk_buff {scalar_t__ mark; } ;
struct nf_hook_state {TYPE_2__* net; } ;
struct iphdr {scalar_t__ saddr; scalar_t__ daddr; scalar_t__ tos; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  iptable_mangle; } ;
struct TYPE_4__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 unsigned int NF_DROP ; 
 unsigned int NF_DROP_ERR (int) ; 
 unsigned int NF_STOLEN ; 
 int /*<<< orphan*/  RTN_UNSPEC ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_route_me_harder (TYPE_2__*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned int ipt_do_table (struct sk_buff*,struct nf_hook_state const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ipt_mangle_out(struct sk_buff *skb, const struct nf_hook_state *state)
{
	unsigned int ret;
	const struct iphdr *iph;
	u_int8_t tos;
	__be32 saddr, daddr;
	u_int32_t mark;
	int err;

	/* Save things which could affect route */
	mark = skb->mark;
	iph = ip_hdr(skb);
	saddr = iph->saddr;
	daddr = iph->daddr;
	tos = iph->tos;

	ret = ipt_do_table(skb, state, state->net->ipv4.iptable_mangle);
	/* Reroute for ANY change. */
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