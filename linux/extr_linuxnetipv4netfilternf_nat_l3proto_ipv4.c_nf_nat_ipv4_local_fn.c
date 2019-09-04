#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  net; } ;
struct nf_conn {TYPE_6__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_9__ {scalar_t__ ip; } ;
struct TYPE_10__ {TYPE_3__ u3; } ;
struct TYPE_7__ {scalar_t__ ip; } ;
struct TYPE_8__ {TYPE_1__ u3; } ;
struct TYPE_11__ {TYPE_4__ src; TYPE_2__ dst; } ;
struct TYPE_12__ {TYPE_5__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 unsigned int NF_DROP ; 
 unsigned int NF_DROP_ERR (int) ; 
 unsigned int NF_STOLEN ; 
 int /*<<< orphan*/  RTN_UNSPEC ; 
 int ip_route_me_harder (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 unsigned int nf_nat_ipv4_fn (void*,struct sk_buff*,struct nf_hook_state const*) ; 

__attribute__((used)) static unsigned int
nf_nat_ipv4_local_fn(void *priv, struct sk_buff *skb,
		     const struct nf_hook_state *state)
{
	const struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	unsigned int ret;
	int err;

	ret = nf_nat_ipv4_fn(priv, skb, state);
	if (ret != NF_DROP && ret != NF_STOLEN &&
	    (ct = nf_ct_get(skb, &ctinfo)) != NULL) {
		enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);

		if (ct->tuplehash[dir].tuple.dst.u3.ip !=
		    ct->tuplehash[!dir].tuple.src.u3.ip) {
			err = ip_route_me_harder(state->net, skb, RTN_UNSPEC);
			if (err < 0)
				ret = NF_DROP_ERR(err);
		}
#ifdef CONFIG_XFRM
		else if (!(IPCB(skb)->flags & IPSKB_XFRM_TRANSFORMED) &&
			 ct->tuplehash[dir].tuple.dst.protonum != IPPROTO_ICMP &&
			 ct->tuplehash[dir].tuple.dst.u.all !=
			 ct->tuplehash[!dir].tuple.src.u.all) {
			err = nf_xfrm_me_harder(state->net, skb, AF_INET);
			if (err < 0)
				ret = NF_DROP_ERR(err);
		}
#endif
	}
	return ret;
}