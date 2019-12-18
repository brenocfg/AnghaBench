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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct netlink_skb_parms {int /*<<< orphan*/  portid; } ;
struct dn_fib_node {int /*<<< orphan*/  fn_key; int /*<<< orphan*/  fn_scope; int /*<<< orphan*/  fn_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DN_FIB_INFO (struct dn_fib_node*) ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTNLGRP_DECnet_ROUTE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int dn_fib_dump_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_fib_nlmsg_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dn_rtmsg_fib(int event, struct dn_fib_node *f, int z, u32 tb_id,
			struct nlmsghdr *nlh, struct netlink_skb_parms *req)
{
	struct sk_buff *skb;
	u32 portid = req ? req->portid : 0;
	int err = -ENOBUFS;

	skb = nlmsg_new(dn_fib_nlmsg_size(DN_FIB_INFO(f)), GFP_KERNEL);
	if (skb == NULL)
		goto errout;

	err = dn_fib_dump_info(skb, portid, nlh->nlmsg_seq, event, tb_id,
			       f->fn_type, f->fn_scope, &f->fn_key, z,
			       DN_FIB_INFO(f), 0);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in dn_fib_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	rtnl_notify(skb, &init_net, portid, RTNLGRP_DECnet_ROUTE, nlh, GFP_KERNEL);
	return;
errout:
	if (err < 0)
		rtnl_set_sk_err(&init_net, RTNLGRP_DECnet_ROUTE, err);
}