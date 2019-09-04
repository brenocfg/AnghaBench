#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rtmsg {int rtm_flags; } ;
struct rt6_rtnl_dump_arg {TYPE_2__* cb; int /*<<< orphan*/  skb; struct net* net; } ;
struct TYPE_6__ {struct fib6_info* fib6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_info {int fib6_flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  portid; } ;
struct TYPE_8__ {int /*<<< orphan*/  nlmsg_seq; } ;
struct TYPE_7__ {TYPE_3__* nlh; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 TYPE_5__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int RTF_PREFIX_RT ; 
 int RTM_F_PREFIX ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 struct rtmsg* nlmsg_data (TYPE_3__*) ; 
 int nlmsg_len (TYPE_3__*) ; 
 int rt6_fill_node (struct net*,int /*<<< orphan*/ ,struct fib6_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rt6_dump_route(struct fib6_info *rt, void *p_arg)
{
	struct rt6_rtnl_dump_arg *arg = (struct rt6_rtnl_dump_arg *) p_arg;
	struct net *net = arg->net;

	if (rt == net->ipv6.fib6_null_entry)
		return 0;

	if (nlmsg_len(arg->cb->nlh) >= sizeof(struct rtmsg)) {
		struct rtmsg *rtm = nlmsg_data(arg->cb->nlh);

		/* user wants prefix routes only */
		if (rtm->rtm_flags & RTM_F_PREFIX &&
		    !(rt->fib6_flags & RTF_PREFIX_RT)) {
			/* success since this is not a prefix route */
			return 1;
		}
	}

	return rt6_fill_node(net, arg->skb, rt, NULL, NULL, NULL, 0,
			     RTM_NEWROUTE, NETLINK_CB(arg->cb->skb).portid,
			     arg->cb->nlh->nlmsg_seq, NLM_F_MULTI);
}