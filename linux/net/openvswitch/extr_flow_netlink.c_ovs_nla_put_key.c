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
struct sw_flow_key {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int __ovs_nla_put_key (struct sw_flow_key const*,struct sw_flow_key const*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int) ; 

int ovs_nla_put_key(const struct sw_flow_key *swkey,
		    const struct sw_flow_key *output, int attr, bool is_mask,
		    struct sk_buff *skb)
{
	int err;
	struct nlattr *nla;

	nla = nla_nest_start_noflag(skb, attr);
	if (!nla)
		return -EMSGSIZE;
	err = __ovs_nla_put_key(swkey, output, is_mask, skb);
	if (err)
		return err;
	nla_nest_end(skb, nla);

	return 0;
}