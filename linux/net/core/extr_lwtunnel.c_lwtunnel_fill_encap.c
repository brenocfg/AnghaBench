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
struct nlattr {int dummy; } ;
struct lwtunnel_state {size_t type; } ;
struct lwtunnel_encap_ops {int (* fill_encap ) (struct sk_buff*,struct lwtunnel_state*) ;} ;

/* Variables and functions */
 int EMSGSIZE ; 
 int EOPNOTSUPP ; 
 size_t LWTUNNEL_ENCAP_MAX ; 
 size_t LWTUNNEL_ENCAP_NONE ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lwtun_encaps ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int) ; 
 int nla_put_u16 (struct sk_buff*,int,size_t) ; 
 struct lwtunnel_encap_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (struct sk_buff*,struct lwtunnel_state*) ; 

int lwtunnel_fill_encap(struct sk_buff *skb, struct lwtunnel_state *lwtstate,
			int encap_attr, int encap_type_attr)
{
	const struct lwtunnel_encap_ops *ops;
	struct nlattr *nest;
	int ret;

	if (!lwtstate)
		return 0;

	if (lwtstate->type == LWTUNNEL_ENCAP_NONE ||
	    lwtstate->type > LWTUNNEL_ENCAP_MAX)
		return 0;

	nest = nla_nest_start_noflag(skb, encap_attr);
	if (!nest)
		return -EMSGSIZE;

	ret = -EOPNOTSUPP;
	rcu_read_lock();
	ops = rcu_dereference(lwtun_encaps[lwtstate->type]);
	if (likely(ops && ops->fill_encap))
		ret = ops->fill_encap(skb, lwtstate);
	rcu_read_unlock();

	if (ret)
		goto nla_put_failure;
	nla_nest_end(skb, nest);
	ret = nla_put_u16(skb, encap_type_attr, lwtstate->type);
	if (ret)
		goto nla_put_failure;

	return 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);

	return (ret == -EOPNOTSUPP ? 0 : ret);
}