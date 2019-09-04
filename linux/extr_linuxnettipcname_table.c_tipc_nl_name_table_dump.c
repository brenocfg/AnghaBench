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
typedef  void* u32 ;
struct tipc_nl_msg {int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; struct sk_buff* skb; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netlink_callback {int* args; int prev_seq; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int tipc_nl_service_list (struct net*,struct tipc_nl_msg*,void**,void**,void**) ; 

int tipc_nl_name_table_dump(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	u32 last_type = cb->args[0];
	u32 last_lower = cb->args[1];
	u32 last_key = cb->args[2];
	int done = cb->args[3];
	struct tipc_nl_msg msg;
	int err;

	if (done)
		return 0;

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	rcu_read_lock();
	err = tipc_nl_service_list(net, &msg, &last_type,
				   &last_lower, &last_key);
	if (!err) {
		done = 1;
	} else if (err != -EMSGSIZE) {
		/* We never set seq or call nl_dump_check_consistent() this
		 * means that setting prev_seq here will cause the consistence
		 * check to fail in the netlink callback handler. Resulting in
		 * the NLMSG_DONE message having the NLM_F_DUMP_INTR flag set if
		 * we got an error.
		 */
		cb->prev_seq = 1;
	}
	rcu_read_unlock();

	cb->args[0] = last_type;
	cb->args[1] = last_lower;
	cb->args[2] = last_key;
	cb->args[3] = done;

	return skb->len;
}