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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct netlink_dump_control {int /*<<< orphan*/  done; int /*<<< orphan*/  dump; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int NLM_F_DUMP ; 
 int /*<<< orphan*/  ctnetlink_done_list ; 
 int /*<<< orphan*/  ctnetlink_dump_unconfirmed ; 
 int netlink_dump_start (struct sock*,struct sk_buff*,struct nlmsghdr const*,struct netlink_dump_control*) ; 

__attribute__((used)) static int ctnetlink_get_ct_unconfirmed(struct net *net, struct sock *ctnl,
					struct sk_buff *skb,
					const struct nlmsghdr *nlh,
					const struct nlattr * const cda[],
					struct netlink_ext_ack *extack)
{
	if (nlh->nlmsg_flags & NLM_F_DUMP) {
		struct netlink_dump_control c = {
			.dump = ctnetlink_dump_unconfirmed,
			.done = ctnetlink_done_list,
		};
		return netlink_dump_start(ctnl, skb, nlh, &c);
	}

	return -EOPNOTSUPP;
}