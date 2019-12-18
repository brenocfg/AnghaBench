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
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct fl_flow_key {int dummy; } ;
struct fl_flow_tmplt {struct fl_flow_key mask; struct fl_flow_key dummy_key; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 scalar_t__ fl_dump_key (struct sk_buff*,struct net*,struct fl_flow_key*,struct fl_flow_key*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fl_tmplt_dump(struct sk_buff *skb, struct net *net, void *tmplt_priv)
{
	struct fl_flow_tmplt *tmplt = tmplt_priv;
	struct fl_flow_key *key, *mask;
	struct nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (!nest)
		goto nla_put_failure;

	key = &tmplt->dummy_key;
	mask = &tmplt->mask;

	if (fl_dump_key(skb, net, key, mask))
		goto nla_put_failure;

	nla_nest_end(skb, nest);

	return skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -EMSGSIZE;
}