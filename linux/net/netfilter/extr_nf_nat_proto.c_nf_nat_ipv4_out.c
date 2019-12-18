#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  net; } ;
struct nf_conn {TYPE_8__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_18__ {int flags; } ;
struct TYPE_14__ {scalar_t__ all; } ;
struct TYPE_11__ {scalar_t__ ip; } ;
struct TYPE_15__ {scalar_t__ protonum; TYPE_5__ u; TYPE_2__ u3; } ;
struct TYPE_12__ {scalar_t__ all; } ;
struct TYPE_10__ {scalar_t__ ip; } ;
struct TYPE_13__ {TYPE_3__ u; TYPE_1__ u3; } ;
struct TYPE_16__ {TYPE_6__ dst; TYPE_4__ src; } ;
struct TYPE_17__ {TYPE_7__ tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int CTINFO2DIR (int) ; 
 TYPE_9__* IPCB (struct sk_buff*) ; 
 scalar_t__ IPPROTO_ICMP ; 
 int IPSKB_XFRM_TRANSFORMED ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP_ERR (int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 unsigned int nf_nat_ipv4_fn (void*,struct sk_buff*,struct nf_hook_state const*) ; 
 int nf_xfrm_me_harder (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 

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
	if (ret != NF_ACCEPT)
		return ret;

	if (IPCB(skb)->flags & IPSKB_XFRM_TRANSFORMED)
		return ret;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct) {
		enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);

		if (ct->tuplehash[dir].tuple.src.u3.ip !=
		     ct->tuplehash[!dir].tuple.dst.u3.ip ||
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