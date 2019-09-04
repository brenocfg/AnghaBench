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
struct sk_buff {int len; } ;
struct nlmsghdr {int nlmsg_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  RCV_SKB_FAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void dnrmg_receive_user_skb(struct sk_buff *skb)
{
	struct nlmsghdr *nlh = nlmsg_hdr(skb);

	if (skb->len < sizeof(*nlh) ||
	    nlh->nlmsg_len < sizeof(*nlh) ||
	    skb->len < nlh->nlmsg_len)
		return;

	if (!netlink_capable(skb, CAP_NET_ADMIN))
		RCV_SKB_FAIL(-EPERM);

	/* Eventually we might send routing messages too */

	RCV_SKB_FAIL(-EINVAL);
}