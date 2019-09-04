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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {scalar_t__ nlmsg_type; int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netlink_dump_control {int /*<<< orphan*/  dump; } ;
struct net {int /*<<< orphan*/  diag_nlsk; } ;
struct inet_diag_req {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INET_DIAG_GETSOCK_MAX ; 
 int /*<<< orphan*/  INET_DIAG_REQ_BYTECODE ; 
 int NLM_F_DUMP ; 
 int inet_diag_bc_audit (struct nlattr*,struct sk_buff*) ; 
 int /*<<< orphan*/  inet_diag_dump_compat ; 
 int inet_diag_get_exact_compat (struct sk_buff*,struct nlmsghdr*) ; 
 int netlink_dump_start (int /*<<< orphan*/ ,struct sk_buff*,struct nlmsghdr*,struct netlink_dump_control*) ; 
 scalar_t__ nlmsg_attrlen (struct nlmsghdr*,int) ; 
 struct nlattr* nlmsg_find_attr (struct nlmsghdr*,int,int /*<<< orphan*/ ) ; 
 int nlmsg_len (struct nlmsghdr*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_diag_rcv_msg_compat(struct sk_buff *skb, struct nlmsghdr *nlh)
{
	int hdrlen = sizeof(struct inet_diag_req);
	struct net *net = sock_net(skb->sk);

	if (nlh->nlmsg_type >= INET_DIAG_GETSOCK_MAX ||
	    nlmsg_len(nlh) < hdrlen)
		return -EINVAL;

	if (nlh->nlmsg_flags & NLM_F_DUMP) {
		if (nlmsg_attrlen(nlh, hdrlen)) {
			struct nlattr *attr;
			int err;

			attr = nlmsg_find_attr(nlh, hdrlen,
					       INET_DIAG_REQ_BYTECODE);
			err = inet_diag_bc_audit(attr, skb);
			if (err)
				return err;
		}
		{
			struct netlink_dump_control c = {
				.dump = inet_diag_dump_compat,
			};
			return netlink_dump_start(net->diag_nlsk, skb, nlh, &c);
		}
	}

	return inet_diag_get_exact_compat(skb, nlh);
}