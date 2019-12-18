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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_proto {int dummy; } ;
struct tcf_chain {int dummy; } ;
struct tcf_block {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct net {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct tcf_proto* tcf_get_next_proto (struct tcf_chain*,struct tcf_proto*,int) ; 
 int /*<<< orphan*/  tfilter_notify (struct net*,struct sk_buff*,struct nlmsghdr*,struct tcf_proto*,struct tcf_block*,struct Qdisc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void tfilter_notify_chain(struct net *net, struct sk_buff *oskb,
				 struct tcf_block *block, struct Qdisc *q,
				 u32 parent, struct nlmsghdr *n,
				 struct tcf_chain *chain, int event,
				 bool rtnl_held)
{
	struct tcf_proto *tp;

	for (tp = tcf_get_next_proto(chain, NULL, rtnl_held);
	     tp; tp = tcf_get_next_proto(chain, tp, rtnl_held))
		tfilter_notify(net, oskb, n, tp, block,
			       q, parent, NULL, event, false, rtnl_held);
}