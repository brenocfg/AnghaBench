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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct net_device {unsigned int num_tx_queues; int flags; struct Qdisc* qdisc; } ;
struct net {int dummy; } ;
struct Qdisc_class_ops {int (* graft ) (struct Qdisc*,unsigned long,struct Qdisc*,struct Qdisc**,struct netlink_ext_ack*) ;unsigned long (* find ) (struct Qdisc*,int /*<<< orphan*/ ) ;} ;
struct Qdisc {int flags; TYPE_1__* ops; } ;
struct TYPE_2__ {struct Qdisc_class_ops* cl_ops; int /*<<< orphan*/  (* attach ) (struct Qdisc*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int TCQ_F_INGRESS ; 
 int TCQ_F_NOLOCK ; 
 int /*<<< orphan*/  dev_activate (struct net_device*) ; 
 int /*<<< orphan*/  dev_deactivate (struct net_device*) ; 
 struct Qdisc* dev_graft_qdisc (struct netdev_queue*,struct Qdisc*) ; 
 struct netdev_queue* dev_ingress_queue (struct net_device*) ; 
 struct net* dev_net (struct net_device*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,unsigned int) ; 
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/  notify_and_destroy (struct net*,struct sk_buff*,struct nlmsghdr*,int /*<<< orphan*/ ,struct Qdisc*,struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_clear_nolock (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_offload_graft_root (struct net_device*,struct Qdisc*,struct Qdisc*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  qdisc_put (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_refcount_inc (struct Qdisc*) ; 
 int /*<<< orphan*/  stub1 (struct Qdisc*) ; 
 unsigned long stub2 (struct Qdisc*,int /*<<< orphan*/ ) ; 
 int stub3 (struct Qdisc*,unsigned long,struct Qdisc*,struct Qdisc**,struct netlink_ext_ack*) ; 

__attribute__((used)) static int qdisc_graft(struct net_device *dev, struct Qdisc *parent,
		       struct sk_buff *skb, struct nlmsghdr *n, u32 classid,
		       struct Qdisc *new, struct Qdisc *old,
		       struct netlink_ext_ack *extack)
{
	struct Qdisc *q = old;
	struct net *net = dev_net(dev);

	if (parent == NULL) {
		unsigned int i, num_q, ingress;

		ingress = 0;
		num_q = dev->num_tx_queues;
		if ((q && q->flags & TCQ_F_INGRESS) ||
		    (new && new->flags & TCQ_F_INGRESS)) {
			num_q = 1;
			ingress = 1;
			if (!dev_ingress_queue(dev)) {
				NL_SET_ERR_MSG(extack, "Device does not have an ingress queue");
				return -ENOENT;
			}
		}

		if (dev->flags & IFF_UP)
			dev_deactivate(dev);

		qdisc_offload_graft_root(dev, new, old, extack);

		if (new && new->ops->attach)
			goto skip;

		for (i = 0; i < num_q; i++) {
			struct netdev_queue *dev_queue = dev_ingress_queue(dev);

			if (!ingress)
				dev_queue = netdev_get_tx_queue(dev, i);

			old = dev_graft_qdisc(dev_queue, new);
			if (new && i > 0)
				qdisc_refcount_inc(new);

			if (!ingress)
				qdisc_put(old);
		}

skip:
		if (!ingress) {
			notify_and_destroy(net, skb, n, classid,
					   dev->qdisc, new);
			if (new && !new->ops->attach)
				qdisc_refcount_inc(new);
			dev->qdisc = new ? : &noop_qdisc;

			if (new && new->ops->attach)
				new->ops->attach(new);
		} else {
			notify_and_destroy(net, skb, n, classid, old, new);
		}

		if (dev->flags & IFF_UP)
			dev_activate(dev);
	} else {
		const struct Qdisc_class_ops *cops = parent->ops->cl_ops;
		unsigned long cl;
		int err;

		/* Only support running class lockless if parent is lockless */
		if (new && (new->flags & TCQ_F_NOLOCK) &&
		    parent && !(parent->flags & TCQ_F_NOLOCK))
			qdisc_clear_nolock(new);

		if (!cops || !cops->graft)
			return -EOPNOTSUPP;

		cl = cops->find(parent, classid);
		if (!cl) {
			NL_SET_ERR_MSG(extack, "Specified class not found");
			return -ENOENT;
		}

		err = cops->graft(parent, cl, new, &old, extack);
		if (err)
			return err;
		notify_and_destroy(net, skb, n, classid, old, new);
	}
	return 0;
}