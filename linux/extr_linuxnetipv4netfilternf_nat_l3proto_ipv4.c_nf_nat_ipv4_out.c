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
struct sk_buff {int dummy; } ;
struct nf_hook_state {int dummy; } ;

/* Variables and functions */
 unsigned int nf_nat_ipv4_fn (void*,struct sk_buff*,struct nf_hook_state const*) ; 

__attribute__((used)) static unsigned int
nf_nat_ipv4_out(void *priv, struct sk_buff *skb,
		const struct nf_hook_state *state)
{
#ifdef CONFIG_XFRM
	const struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	int err;
#endif
	unsigned int ret;

	ret = nf_nat_ipv4_fn(priv, skb, state);
#ifdef CONFIG_XFRM
	if (ret != NF_DROP && ret != NF_STOLEN &&
	    !(IPCB(skb)->flags & IPSKB_XFRM_TRANSFORMED) &&
	    (ct = nf_ct_get(skb, &ctinfo)) != NULL) {
		enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);

		if ((ct->tuplehash[dir].tuple.src.u3.ip !=
		     ct->tuplehash[!dir].tuple.dst.u3.ip) ||
		    (ct->tuplehash[dir].tuple.dst.protonum != IPPROTO_ICMP &&
		     ct->tuplehash[dir].tuple.src.u.all !=
		     ct->tuplehash[!dir].tuple.dst.u.all)) {
			err = nf_xfrm_me_harder(state->net, skb, AF_INET);
			if (err < 0)
				ret = NF_DROP_ERR(err);
		}
	}
#endif
	return ret;
}