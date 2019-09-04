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
struct tipc_sock_diag_req {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct netlink_dump_control {int /*<<< orphan*/  done; int /*<<< orphan*/  dump; int /*<<< orphan*/  start; } ;
struct net {int /*<<< orphan*/  diag_nlsk; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int NLM_F_DUMP ; 
 int /*<<< orphan*/  netlink_dump_start (int /*<<< orphan*/ ,struct sk_buff*,struct nlmsghdr*,struct netlink_dump_control*) ; 
 int nlmsg_len (struct nlmsghdr*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_diag_dump ; 
 int /*<<< orphan*/  tipc_dump_done ; 
 int /*<<< orphan*/  tipc_dump_start ; 

__attribute__((used)) static int tipc_sock_diag_handler_dump(struct sk_buff *skb,
				       struct nlmsghdr *h)
{
	int hdrlen = sizeof(struct tipc_sock_diag_req);
	struct net *net = sock_net(skb->sk);

	if (nlmsg_len(h) < hdrlen)
		return -EINVAL;

	if (h->nlmsg_flags & NLM_F_DUMP) {
		struct netlink_dump_control c = {
			.start = tipc_dump_start,
			.dump = tipc_diag_dump,
			.done = tipc_dump_done,
		};
		netlink_dump_start(net->diag_nlsk, skb, h, &c);
		return 0;
	}
	return -EOPNOTSUPP;
}