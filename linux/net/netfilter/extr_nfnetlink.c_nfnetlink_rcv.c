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
struct sk_buff {scalar_t__ len; } ;
struct nlmsghdr {scalar_t__ nlmsg_len; scalar_t__ nlmsg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  EPERM ; 
 scalar_t__ NFNL_MSG_BATCH_BEGIN ; 
 scalar_t__ NLMSG_HDRLEN ; 
 int /*<<< orphan*/  netlink_ack (struct sk_buff*,struct nlmsghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlink_net_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_rcv_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_rcv_msg ; 
 int /*<<< orphan*/  nfnetlink_rcv_skb_batch (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 

__attribute__((used)) static void nfnetlink_rcv(struct sk_buff *skb)
{
	struct nlmsghdr *nlh = nlmsg_hdr(skb);

	if (skb->len < NLMSG_HDRLEN ||
	    nlh->nlmsg_len < NLMSG_HDRLEN ||
	    skb->len < nlh->nlmsg_len)
		return;

	if (!netlink_net_capable(skb, CAP_NET_ADMIN)) {
		netlink_ack(skb, nlh, -EPERM, NULL);
		return;
	}

	if (nlh->nlmsg_type == NFNL_MSG_BATCH_BEGIN)
		nfnetlink_rcv_skb_batch(skb, nlh);
	else
		netlink_rcv_skb(skb, nfnetlink_rcv_msg);
}