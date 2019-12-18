#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tipc_nl_msg {int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; struct sk_buff* skb; } ;
struct tipc_net {int /*<<< orphan*/ * bearer_list; } ;
struct tipc_bearer {int dummy; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int MAX_BEARERS ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int __tipc_nl_add_bearer (struct tipc_nl_msg*,struct tipc_bearer*,int /*<<< orphan*/ ) ; 
 struct tipc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tipc_bearer* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_net_id ; 

int tipc_nl_bearer_dump(struct sk_buff *skb, struct netlink_callback *cb)
{
	int err;
	int i = cb->args[0];
	struct tipc_bearer *bearer;
	struct tipc_nl_msg msg;
	struct net *net = sock_net(skb->sk);
	struct tipc_net *tn = net_generic(net, tipc_net_id);

	if (i == MAX_BEARERS)
		return 0;

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	rtnl_lock();
	for (i = 0; i < MAX_BEARERS; i++) {
		bearer = rtnl_dereference(tn->bearer_list[i]);
		if (!bearer)
			continue;

		err = __tipc_nl_add_bearer(&msg, bearer, NLM_F_MULTI);
		if (err)
			break;
	}
	rtnl_unlock();

	cb->args[0] = i;
	return skb->len;
}