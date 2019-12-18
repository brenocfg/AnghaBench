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
struct net_fill_args {int cmd; int nsid; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RTNLGRP_NSID ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnl_net_fill (struct sk_buff*,struct net_fill_args*) ; 
 int /*<<< orphan*/  rtnl_net_get_size () ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtnl_net_notifyid(struct net *net, int cmd, int id, u32 portid,
			      struct nlmsghdr *nlh, gfp_t gfp)
{
	struct net_fill_args fillargs = {
		.portid = portid,
		.seq = nlh ? nlh->nlmsg_seq : 0,
		.cmd = cmd,
		.nsid = id,
	};
	struct sk_buff *msg;
	int err = -ENOMEM;

	msg = nlmsg_new(rtnl_net_get_size(), gfp);
	if (!msg)
		goto out;

	err = rtnl_net_fill(msg, &fillargs);
	if (err < 0)
		goto err_out;

	rtnl_notify(msg, net, portid, RTNLGRP_NSID, nlh, gfp);
	return;

err_out:
	nlmsg_free(msg);
out:
	rtnl_set_sk_err(net, RTNLGRP_NSID, err);
}