#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct sk_buff {scalar_t__ mark; } ;
struct nf_hook_state {TYPE_3__* net; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  saddr ;
typedef  int /*<<< orphan*/  daddr ;
struct TYPE_4__ {int /*<<< orphan*/  ip6table_mangle; } ;
struct TYPE_6__ {TYPE_1__ ipv6; } ;
struct TYPE_5__ {scalar_t__ hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 unsigned int NF_DROP ; 
 unsigned int NF_DROP_ERR (int) ; 
 unsigned int NF_STOLEN ; 
 int ip6_route_me_harder (TYPE_3__*,struct sk_buff*) ; 
 unsigned int ip6t_do_table (struct sk_buff*,struct nf_hook_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int
ip6t_mangle_out(struct sk_buff *skb, const struct nf_hook_state *state)
{
	unsigned int ret;
	struct in6_addr saddr, daddr;
	u_int8_t hop_limit;
	u_int32_t flowlabel, mark;
	int err;

	/* save source/dest address, mark, hoplimit, flowlabel, priority,  */
	memcpy(&saddr, &ipv6_hdr(skb)->saddr, sizeof(saddr));
	memcpy(&daddr, &ipv6_hdr(skb)->daddr, sizeof(daddr));
	mark = skb->mark;
	hop_limit = ipv6_hdr(skb)->hop_limit;

	/* flowlabel and prio (includes version, which shouldn't change either */
	flowlabel = *((u_int32_t *)ipv6_hdr(skb));

	ret = ip6t_do_table(skb, state, state->net->ipv6.ip6table_mangle);

	if (ret != NF_DROP && ret != NF_STOLEN &&
	    (!ipv6_addr_equal(&ipv6_hdr(skb)->saddr, &saddr) ||
	     !ipv6_addr_equal(&ipv6_hdr(skb)->daddr, &daddr) ||
	     skb->mark != mark ||
	     ipv6_hdr(skb)->hop_limit != hop_limit ||
	     flowlabel != *((u_int32_t *)ipv6_hdr(skb)))) {
		err = ip6_route_me_harder(state->net, skb);
		if (err < 0)
			ret = NF_DROP_ERR(err);
	}

	return ret;
}