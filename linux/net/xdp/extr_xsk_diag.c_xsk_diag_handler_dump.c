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
struct xdp_diag_req {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct netlink_dump_control {int /*<<< orphan*/  dump; } ;
struct net {int /*<<< orphan*/  diag_nlsk; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int NLM_F_DUMP ; 
 int netlink_dump_start (int /*<<< orphan*/ ,struct sk_buff*,struct nlmsghdr*,struct netlink_dump_control*) ; 
 int nlmsg_len (struct nlmsghdr*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_diag_dump ; 

__attribute__((used)) static int xsk_diag_handler_dump(struct sk_buff *nlskb, struct nlmsghdr *hdr)
{
	struct netlink_dump_control c = { .dump = xsk_diag_dump };
	int hdrlen = sizeof(struct xdp_diag_req);
	struct net *net = sock_net(nlskb->sk);

	if (nlmsg_len(hdr) < hdrlen)
		return -EINVAL;

	if (!(hdr->nlmsg_flags & NLM_F_DUMP))
		return -EOPNOTSUPP;

	return netlink_dump_start(net->diag_nlsk, nlskb, hdr, &c);
}