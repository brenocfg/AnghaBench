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
struct tipc_nl_msg {int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int __tipc_nl_add_monitor_prop (struct net*,struct tipc_nl_msg*) ; 
 int genlmsg_reply (int /*<<< orphan*/ ,struct genl_info*) ; 
 int /*<<< orphan*/  nlmsg_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

int tipc_nl_node_get_monitor(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = sock_net(skb->sk);
	struct tipc_nl_msg msg;
	int err;

	msg.skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!msg.skb)
		return -ENOMEM;
	msg.portid = info->snd_portid;
	msg.seq = info->snd_seq;

	err = __tipc_nl_add_monitor_prop(net, &msg);
	if (err) {
		nlmsg_free(msg.skb);
		return err;
	}

	return genlmsg_reply(msg.skb, info);
}