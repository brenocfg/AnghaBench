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
struct netlink_dump_control {int /*<<< orphan*/  min_dump_alloc; int /*<<< orphan*/  dump; } ;
struct net {int /*<<< orphan*/  diag_nlsk; } ;

/* Variables and functions */
 int NLM_F_DUMP ; 
 int /*<<< orphan*/  SKB_WITH_OVERHEAD (int) ; 
 scalar_t__ SOCK_DIAG_BY_FAMILY ; 
 int netlink_dump_start (int /*<<< orphan*/ ,struct sk_buff*,struct nlmsghdr*,struct netlink_dump_control*) ; 
 int /*<<< orphan*/  smc_diag_dump ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_diag_handler_dump(struct sk_buff *skb, struct nlmsghdr *h)
{
	struct net *net = sock_net(skb->sk);

	if (h->nlmsg_type == SOCK_DIAG_BY_FAMILY &&
	    h->nlmsg_flags & NLM_F_DUMP) {
		{
			struct netlink_dump_control c = {
				.dump = smc_diag_dump,
				.min_dump_alloc = SKB_WITH_OVERHEAD(32768),
			};
			return netlink_dump_start(net->diag_nlsk, skb, h, &c);
		}
	}
	return 0;
}