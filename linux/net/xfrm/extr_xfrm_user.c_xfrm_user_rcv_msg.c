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
struct xfrm_link {int (* doit ) (struct sk_buff*,struct nlmsghdr*,struct nlattr**) ;scalar_t__ nla_pol; scalar_t__ nla_max; int /*<<< orphan*/  done; int /*<<< orphan*/ * dump; int /*<<< orphan*/  start; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_type; int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct netlink_dump_control {int /*<<< orphan*/  done; int /*<<< orphan*/ * dump; int /*<<< orphan*/  start; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlsk; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int NLM_F_DUMP ; 
 int /*<<< orphan*/  XFRMA_MAX ; 
 int XFRM_MSG_BASE ; 
 int XFRM_MSG_GETPOLICY ; 
 int XFRM_MSG_GETSA ; 
 int XFRM_MSG_MAX ; 
 scalar_t__ in_compat_syscall () ; 
 int netlink_dump_start (int /*<<< orphan*/ ,struct sk_buff*,struct nlmsghdr*,struct netlink_dump_control*) ; 
 int /*<<< orphan*/  netlink_net_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int /*<<< orphan*/ ,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,struct nlmsghdr*,struct nlattr**) ; 
 struct xfrm_link* xfrm_dispatch ; 
 int /*<<< orphan*/ * xfrm_msg_min ; 
 int /*<<< orphan*/  xfrma_policy ; 

__attribute__((used)) static int xfrm_user_rcv_msg(struct sk_buff *skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *attrs[XFRMA_MAX+1];
	const struct xfrm_link *link;
	int type, err;

	if (in_compat_syscall())
		return -EOPNOTSUPP;

	type = nlh->nlmsg_type;
	if (type > XFRM_MSG_MAX)
		return -EINVAL;

	type -= XFRM_MSG_BASE;
	link = &xfrm_dispatch[type];

	/* All operations require privileges, even GET */
	if (!netlink_net_capable(skb, CAP_NET_ADMIN))
		return -EPERM;

	if ((type == (XFRM_MSG_GETSA - XFRM_MSG_BASE) ||
	     type == (XFRM_MSG_GETPOLICY - XFRM_MSG_BASE)) &&
	    (nlh->nlmsg_flags & NLM_F_DUMP)) {
		if (link->dump == NULL)
			return -EINVAL;

		{
			struct netlink_dump_control c = {
				.start = link->start,
				.dump = link->dump,
				.done = link->done,
			};
			return netlink_dump_start(net->xfrm.nlsk, skb, nlh, &c);
		}
	}

	err = nlmsg_parse_deprecated(nlh, xfrm_msg_min[type], attrs,
				     link->nla_max ? : XFRMA_MAX,
				     link->nla_pol ? : xfrma_policy, extack);
	if (err < 0)
		return err;

	if (link->doit == NULL)
		return -EINVAL;

	return link->doit(skb, nlh, attrs);
}