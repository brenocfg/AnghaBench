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
struct tcmsg {int /*<<< orphan*/  tcm_ifindex; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netlink_callback {int* args; int /*<<< orphan*/  nlh; } ;
struct netdev_queue {int /*<<< orphan*/  qdisc_sleeping; } ;
struct net_device {int /*<<< orphan*/  qdisc; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 struct netdev_queue* dev_ingress_queue (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct tcmsg* nlmsg_data (int /*<<< orphan*/ ) ; 
 int nlmsg_len (int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 scalar_t__ tc_dump_tclass_root (int /*<<< orphan*/ ,struct sk_buff*,struct tcmsg*,struct netlink_callback*,int*,int) ; 

__attribute__((used)) static int tc_dump_tclass(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct tcmsg *tcm = nlmsg_data(cb->nlh);
	struct net *net = sock_net(skb->sk);
	struct netdev_queue *dev_queue;
	struct net_device *dev;
	int t, s_t;

	if (nlmsg_len(cb->nlh) < sizeof(*tcm))
		return 0;
	dev = dev_get_by_index(net, tcm->tcm_ifindex);
	if (!dev)
		return 0;

	s_t = cb->args[0];
	t = 0;

	if (tc_dump_tclass_root(dev->qdisc, skb, tcm, cb, &t, s_t) < 0)
		goto done;

	dev_queue = dev_ingress_queue(dev);
	if (dev_queue &&
	    tc_dump_tclass_root(dev_queue->qdisc_sleeping, skb, tcm, cb,
				&t, s_t) < 0)
		goto done;

done:
	cb->args[0] = t;

	dev_put(dev);
	return skb->len;
}