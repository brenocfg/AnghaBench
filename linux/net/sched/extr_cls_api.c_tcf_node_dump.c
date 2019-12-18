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
struct tcf_walker {int dummy; } ;
struct tcf_proto {int dummy; } ;
struct tcf_dump_args {TYPE_2__* cb; int /*<<< orphan*/  parent; int /*<<< orphan*/  q; int /*<<< orphan*/  block; TYPE_3__* skb; } ;
struct net {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  portid; } ;
struct TYPE_7__ {int /*<<< orphan*/  sk; } ;
struct TYPE_6__ {TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct TYPE_5__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 TYPE_4__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_NEWTFILTER ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int tcf_fill_node (struct net*,TYPE_3__*,struct tcf_proto*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tcf_node_dump(struct tcf_proto *tp, void *n, struct tcf_walker *arg)
{
	struct tcf_dump_args *a = (void *)arg;
	struct net *net = sock_net(a->skb->sk);

	return tcf_fill_node(net, a->skb, tp, a->block, a->q, a->parent,
			     n, NETLINK_CB(a->cb->skb).portid,
			     a->cb->nlh->nlmsg_seq, NLM_F_MULTI,
			     RTM_NEWTFILTER, true);
}