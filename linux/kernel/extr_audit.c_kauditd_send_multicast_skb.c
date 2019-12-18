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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_NLGRP_READLOG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sock* audit_get_sk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  netlink_has_listeners (struct sock*,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  nlmsg_multicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kauditd_send_multicast_skb(struct sk_buff *skb)
{
	struct sk_buff *copy;
	struct sock *sock = audit_get_sk(&init_net);
	struct nlmsghdr *nlh;

	/* NOTE: we are not taking an additional reference for init_net since
	 *       we don't have to worry about it going away */

	if (!netlink_has_listeners(sock, AUDIT_NLGRP_READLOG))
		return;

	/*
	 * The seemingly wasteful skb_copy() rather than bumping the refcount
	 * using skb_get() is necessary because non-standard mods are made to
	 * the skb by the original kaudit unicast socket send routine.  The
	 * existing auditd daemon assumes this breakage.  Fixing this would
	 * require co-ordinating a change in the established protocol between
	 * the kaudit kernel subsystem and the auditd userspace code.  There is
	 * no reason for new multicast clients to continue with this
	 * non-compliance.
	 */
	copy = skb_copy(skb, GFP_KERNEL);
	if (!copy)
		return;
	nlh = nlmsg_hdr(copy);
	nlh->nlmsg_len = skb->len;

	nlmsg_multicast(sock, copy, 0, AUDIT_NLGRP_READLOG, GFP_KERNEL);
}