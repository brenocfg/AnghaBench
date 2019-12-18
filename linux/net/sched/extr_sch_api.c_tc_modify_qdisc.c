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
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct netdev_queue {struct Qdisc* qdisc_sleeping; } ;
struct net_device {struct Qdisc* qdisc; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct Qdisc {scalar_t__ handle; struct netdev_queue* dev_queue; TYPE_2__* ops; } ;
struct TYPE_4__ {TYPE_1__* cl_ops; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {struct netdev_queue* (* select_queue ) (struct Qdisc*,struct tcmsg*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EAGAIN ; 
 int EEXIST ; 
 int EINVAL ; 
 int ELOOP ; 
 int ENODEV ; 
 int ENOENT ; 
 int EPERM ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int NLM_F_REPLACE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 size_t TCA_KIND ; 
 int /*<<< orphan*/  TCA_MAX ; 
 scalar_t__ TC_H_INGRESS ; 
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 scalar_t__ TC_H_MIN (scalar_t__) ; 
 scalar_t__ TC_H_ROOT ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_loop (struct Qdisc*,struct Qdisc*,int /*<<< orphan*/ ) ; 
 struct netdev_queue* dev_ingress_queue (struct net_device*) ; 
 scalar_t__ dev_ingress_queue_create (struct net_device*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_ns_capable (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_strcmp (struct nlattr*,int /*<<< orphan*/ ) ; 
 struct tcmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int qdisc_change (struct Qdisc*,struct nlattr**,struct netlink_ext_ack*) ; 
 struct Qdisc* qdisc_create (struct net_device*,struct netdev_queue*,struct Qdisc*,scalar_t__,scalar_t__,struct nlattr**,int*,struct netlink_ext_ack*) ; 
 int qdisc_graft (struct net_device*,struct Qdisc*,struct sk_buff*,struct nlmsghdr*,scalar_t__,struct Qdisc*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 struct Qdisc* qdisc_leaf (struct Qdisc*,scalar_t__) ; 
 struct Qdisc* qdisc_lookup (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  qdisc_notify (struct net*,struct sk_buff*,struct nlmsghdr*,scalar_t__,int /*<<< orphan*/ *,struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_refcount_inc (struct Qdisc*) ; 
 int /*<<< orphan*/  rtm_tca_policy ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 struct netdev_queue* stub1 (struct Qdisc*,struct tcmsg*) ; 

__attribute__((used)) static int tc_modify_qdisc(struct sk_buff *skb, struct nlmsghdr *n,
			   struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct tcmsg *tcm;
	struct nlattr *tca[TCA_MAX + 1];
	struct net_device *dev;
	u32 clid;
	struct Qdisc *q, *p;
	int err;

	if (!netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		return -EPERM;

replay:
	/* Reinit, just in case something touches this. */
	err = nlmsg_parse_deprecated(n, sizeof(*tcm), tca, TCA_MAX,
				     rtm_tca_policy, extack);
	if (err < 0)
		return err;

	tcm = nlmsg_data(n);
	clid = tcm->tcm_parent;
	q = p = NULL;

	dev = __dev_get_by_index(net, tcm->tcm_ifindex);
	if (!dev)
		return -ENODEV;


	if (clid) {
		if (clid != TC_H_ROOT) {
			if (clid != TC_H_INGRESS) {
				p = qdisc_lookup(dev, TC_H_MAJ(clid));
				if (!p) {
					NL_SET_ERR_MSG(extack, "Failed to find specified qdisc");
					return -ENOENT;
				}
				q = qdisc_leaf(p, clid);
			} else if (dev_ingress_queue_create(dev)) {
				q = dev_ingress_queue(dev)->qdisc_sleeping;
			}
		} else {
			q = dev->qdisc;
		}

		/* It may be default qdisc, ignore it */
		if (q && q->handle == 0)
			q = NULL;

		if (!q || !tcm->tcm_handle || q->handle != tcm->tcm_handle) {
			if (tcm->tcm_handle) {
				if (q && !(n->nlmsg_flags & NLM_F_REPLACE)) {
					NL_SET_ERR_MSG(extack, "NLM_F_REPLACE needed to override");
					return -EEXIST;
				}
				if (TC_H_MIN(tcm->tcm_handle)) {
					NL_SET_ERR_MSG(extack, "Invalid minor handle");
					return -EINVAL;
				}
				q = qdisc_lookup(dev, tcm->tcm_handle);
				if (!q)
					goto create_n_graft;
				if (n->nlmsg_flags & NLM_F_EXCL) {
					NL_SET_ERR_MSG(extack, "Exclusivity flag on, cannot override");
					return -EEXIST;
				}
				if (tca[TCA_KIND] &&
				    nla_strcmp(tca[TCA_KIND], q->ops->id)) {
					NL_SET_ERR_MSG(extack, "Invalid qdisc name");
					return -EINVAL;
				}
				if (q == p ||
				    (p && check_loop(q, p, 0))) {
					NL_SET_ERR_MSG(extack, "Qdisc parent/child loop detected");
					return -ELOOP;
				}
				qdisc_refcount_inc(q);
				goto graft;
			} else {
				if (!q)
					goto create_n_graft;

				/* This magic test requires explanation.
				 *
				 *   We know, that some child q is already
				 *   attached to this parent and have choice:
				 *   either to change it or to create/graft new one.
				 *
				 *   1. We are allowed to create/graft only
				 *   if CREATE and REPLACE flags are set.
				 *
				 *   2. If EXCL is set, requestor wanted to say,
				 *   that qdisc tcm_handle is not expected
				 *   to exist, so that we choose create/graft too.
				 *
				 *   3. The last case is when no flags are set.
				 *   Alas, it is sort of hole in API, we
				 *   cannot decide what to do unambiguously.
				 *   For now we select create/graft, if
				 *   user gave KIND, which does not match existing.
				 */
				if ((n->nlmsg_flags & NLM_F_CREATE) &&
				    (n->nlmsg_flags & NLM_F_REPLACE) &&
				    ((n->nlmsg_flags & NLM_F_EXCL) ||
				     (tca[TCA_KIND] &&
				      nla_strcmp(tca[TCA_KIND], q->ops->id))))
					goto create_n_graft;
			}
		}
	} else {
		if (!tcm->tcm_handle) {
			NL_SET_ERR_MSG(extack, "Handle cannot be zero");
			return -EINVAL;
		}
		q = qdisc_lookup(dev, tcm->tcm_handle);
	}

	/* Change qdisc parameters */
	if (!q) {
		NL_SET_ERR_MSG(extack, "Specified qdisc not found");
		return -ENOENT;
	}
	if (n->nlmsg_flags & NLM_F_EXCL) {
		NL_SET_ERR_MSG(extack, "Exclusivity flag on, cannot modify");
		return -EEXIST;
	}
	if (tca[TCA_KIND] && nla_strcmp(tca[TCA_KIND], q->ops->id)) {
		NL_SET_ERR_MSG(extack, "Invalid qdisc name");
		return -EINVAL;
	}
	err = qdisc_change(q, tca, extack);
	if (err == 0)
		qdisc_notify(net, skb, n, clid, NULL, q);
	return err;

create_n_graft:
	if (!(n->nlmsg_flags & NLM_F_CREATE)) {
		NL_SET_ERR_MSG(extack, "Qdisc not found. To create specify NLM_F_CREATE flag");
		return -ENOENT;
	}
	if (clid == TC_H_INGRESS) {
		if (dev_ingress_queue(dev)) {
			q = qdisc_create(dev, dev_ingress_queue(dev), p,
					 tcm->tcm_parent, tcm->tcm_parent,
					 tca, &err, extack);
		} else {
			NL_SET_ERR_MSG(extack, "Cannot find ingress queue for specified device");
			err = -ENOENT;
		}
	} else {
		struct netdev_queue *dev_queue;

		if (p && p->ops->cl_ops && p->ops->cl_ops->select_queue)
			dev_queue = p->ops->cl_ops->select_queue(p, tcm);
		else if (p)
			dev_queue = p->dev_queue;
		else
			dev_queue = netdev_get_tx_queue(dev, 0);

		q = qdisc_create(dev, dev_queue, p,
				 tcm->tcm_parent, tcm->tcm_handle,
				 tca, &err, extack);
	}
	if (q == NULL) {
		if (err == -EAGAIN)
			goto replay;
		return err;
	}

graft:
	err = qdisc_graft(dev, p, skb, n, clid, q, NULL, extack);
	if (err) {
		if (q)
			qdisc_put(q);
		return err;
	}

	return 0;
}