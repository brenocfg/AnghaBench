#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  net; } ;
struct nf_conn {TYPE_4__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_6__ {int /*<<< orphan*/  u3; } ;
struct TYPE_5__ {int /*<<< orphan*/  u3; } ;
struct TYPE_7__ {TYPE_2__ src; TYPE_1__ dst; } ;
struct TYPE_8__ {TYPE_3__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 unsigned int NF_DROP ; 
 unsigned int NF_DROP_ERR (int) ; 
 unsigned int NF_STOLEN ; 
 int ip6_route_me_harder (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_inet_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int nf_nat_ipv6_fn (void*,struct sk_buff*,struct nf_hook_state const*) ; 

__attribute__((used)) static unsigned int
nf_nat_ipv6_local_fn(void *priv, struct sk_buff *skb,
		     const struct nf_hook_state *state)
{
	const struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	unsigned int ret;
	int err;

	ret = nf_nat_ipv6_fn(priv, skb, state);
	if (ret != NF_DROP && ret != NF_STOLEN &&
	    (ct = nf_ct_get(skb, &ctinfo)) != NULL) {
		enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);

		if (!nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.dst.u3,
				      &ct->tuplehash[!dir].tuple.src.u3)) {
			err = ip6_route_me_harder(state->net, skb);
			if (err < 0)
				ret = NF_DROP_ERR(err);
		}
#ifdef CONFIG_XFRM
		else if (!(IP6CB(skb)->flags & IP6SKB_XFRM_TRANSFORMED) &&
			 ct->tuplehash[dir].tuple.dst.protonum != IPPROTO_ICMPV6 &&
			 ct->tuplehash[dir].tuple.dst.u.all !=
			 ct->tuplehash[!dir].tuple.src.u.all) {
			err = nf_xfrm_me_harder(state->net, skb, AF_INET6);
			if (err < 0)
				ret = NF_DROP_ERR(err);
		}
#endif
	}
	return ret;
}