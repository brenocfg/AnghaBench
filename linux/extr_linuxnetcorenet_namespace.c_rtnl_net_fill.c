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
struct rtgenmsg {int /*<<< orphan*/  rtgen_family; } ;
struct nlmsghdr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  NETNSA_NSID ; 
 scalar_t__ nla_put_s32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct rtgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int rtnl_net_fill(struct sk_buff *skb, u32 portid, u32 seq, int flags,
			 int cmd, struct net *net, int nsid)
{
	struct nlmsghdr *nlh;
	struct rtgenmsg *rth;

	nlh = nlmsg_put(skb, portid, seq, cmd, sizeof(*rth), flags);
	if (!nlh)
		return -EMSGSIZE;

	rth = nlmsg_data(nlh);
	rth->rtgen_family = AF_UNSPEC;

	if (nla_put_s32(skb, NETNSA_NSID, nsid))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}