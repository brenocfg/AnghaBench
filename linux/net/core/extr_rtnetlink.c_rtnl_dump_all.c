#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct rtnl_link {int (* dumpit ) (struct sk_buff*,struct netlink_callback*) ;} ;
struct netlink_callback {int family; scalar_t__ seq; scalar_t__ prev_seq; int /*<<< orphan*/ * args; TYPE_1__* nlh; } ;
typedef  int (* rtnl_dumpit_func ) (struct sk_buff*,struct netlink_callback*) ;
struct TYPE_2__ {int nlmsg_type; } ;

/* Variables and functions */
 int PF_PACKET ; 
 int RTM_BASE ; 
 int RTM_NR_MSGTYPES ; 
 int RTNL_FAMILY_MAX ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct rtnl_link** rcu_dereference_rtnl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtnl_msg_handlers ; 

__attribute__((used)) static int rtnl_dump_all(struct sk_buff *skb, struct netlink_callback *cb)
{
	int idx;
	int s_idx = cb->family;
	int type = cb->nlh->nlmsg_type - RTM_BASE;
	int ret = 0;

	if (s_idx == 0)
		s_idx = 1;

	for (idx = 1; idx <= RTNL_FAMILY_MAX; idx++) {
		struct rtnl_link **tab;
		struct rtnl_link *link;
		rtnl_dumpit_func dumpit;

		if (idx < s_idx || idx == PF_PACKET)
			continue;

		if (type < 0 || type >= RTM_NR_MSGTYPES)
			continue;

		tab = rcu_dereference_rtnl(rtnl_msg_handlers[idx]);
		if (!tab)
			continue;

		link = tab[type];
		if (!link)
			continue;

		dumpit = link->dumpit;
		if (!dumpit)
			continue;

		if (idx > s_idx) {
			memset(&cb->args[0], 0, sizeof(cb->args));
			cb->prev_seq = 0;
			cb->seq = 0;
		}
		ret = dumpit(skb, cb);
		if (ret)
			break;
	}
	cb->family = idx;

	return skb->len ? : ret;
}