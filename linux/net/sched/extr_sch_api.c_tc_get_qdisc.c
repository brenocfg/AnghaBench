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
typedef  scalar_t__ u32 ;
struct tcmsg {scalar_t__ tcm_parent; scalar_t__ tcm_handle; int /*<<< orphan*/  tcm_ifindex; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {scalar_t__ nlmsg_type; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {struct Qdisc* qdisc; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct Qdisc {scalar_t__ handle; TYPE_1__* ops; } ;
struct TYPE_4__ {struct Qdisc* qdisc_sleeping; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 scalar_t__ RTM_DELQDISC ; 
 scalar_t__ RTM_GETQDISC ; 
 size_t TCA_KIND ; 
 int /*<<< orphan*/  TCA_MAX ; 
 scalar_t__ TC_H_INGRESS ; 
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 scalar_t__ TC_H_ROOT ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 TYPE_2__* dev_ingress_queue (struct net_device*) ; 
 int /*<<< orphan*/  netlink_ns_capable (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_strcmp (struct nlattr*,int /*<<< orphan*/ ) ; 
 struct tcmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int qdisc_graft (struct net_device*,struct Qdisc*,struct sk_buff*,struct nlmsghdr*,scalar_t__,int /*<<< orphan*/ *,struct Qdisc*,struct netlink_ext_ack*) ; 
 struct Qdisc* qdisc_leaf (struct Qdisc*,scalar_t__) ; 
 struct Qdisc* qdisc_lookup (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  qdisc_notify (struct net*,struct sk_buff*,struct nlmsghdr*,scalar_t__,int /*<<< orphan*/ *,struct Qdisc*) ; 
 int /*<<< orphan*/  rtm_tca_policy ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc_get_qdisc(struct sk_buff *skb, struct nlmsghdr *n,
			struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct tcmsg *tcm = nlmsg_data(n);
	struct nlattr *tca[TCA_MAX + 1];
	struct net_device *dev;
	u32 clid;
	struct Qdisc *q = NULL;
	struct Qdisc *p = NULL;
	int err;

	if ((n->nlmsg_type != RTM_GETQDISC) &&
	    !netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		return -EPERM;

	err = nlmsg_parse_deprecated(n, sizeof(*tcm), tca, TCA_MAX,
				     rtm_tca_policy, extack);
	if (err < 0)
		return err;

	dev = __dev_get_by_index(net, tcm->tcm_ifindex);
	if (!dev)
		return -ENODEV;

	clid = tcm->tcm_parent;
	if (clid) {
		if (clid != TC_H_ROOT) {
			if (TC_H_MAJ(clid) != TC_H_MAJ(TC_H_INGRESS)) {
				p = qdisc_lookup(dev, TC_H_MAJ(clid));
				if (!p) {
					NL_SET_ERR_MSG(extack, "Failed to find qdisc with specified classid");
					return -ENOENT;
				}
				q = qdisc_leaf(p, clid);
			} else if (dev_ingress_queue(dev)) {
				q = dev_ingress_queue(dev)->qdisc_sleeping;
			}
		} else {
			q = dev->qdisc;
		}
		if (!q) {
			NL_SET_ERR_MSG(extack, "Cannot find specified qdisc on specified device");
			return -ENOENT;
		}

		if (tcm->tcm_handle && q->handle != tcm->tcm_handle) {
			NL_SET_ERR_MSG(extack, "Invalid handle");
			return -EINVAL;
		}
	} else {
		q = qdisc_lookup(dev, tcm->tcm_handle);
		if (!q) {
			NL_SET_ERR_MSG(extack, "Failed to find qdisc with specified handle");
			return -ENOENT;
		}
	}

	if (tca[TCA_KIND] && nla_strcmp(tca[TCA_KIND], q->ops->id)) {
		NL_SET_ERR_MSG(extack, "Invalid qdisc name");
		return -EINVAL;
	}

	if (n->nlmsg_type == RTM_DELQDISC) {
		if (!clid) {
			NL_SET_ERR_MSG(extack, "Classid cannot be zero");
			return -EINVAL;
		}
		if (q->handle == 0) {
			NL_SET_ERR_MSG(extack, "Cannot delete qdisc with handle of zero");
			return -ENOENT;
		}
		err = qdisc_graft(dev, p, skb, n, clid, NULL, q, extack);
		if (err != 0)
			return err;
	} else {
		qdisc_notify(net, skb, n, clid, NULL, q);
	}
	return 0;
}