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
struct nlmsghdr {scalar_t__ nlmsg_type; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct mr_table {int dummy; } ;
struct mfcctl {int mfcc_parent; } ;

/* Variables and functions */
 scalar_t__ RTM_NEWROUTE ; 
 int ipmr_mfc_add (struct net*,struct mr_table*,struct mfcctl*,int,int) ; 
 int ipmr_mfc_delete (struct mr_table*,struct mfcctl*,int) ; 
 int rtm_to_ipmr_mfcc (struct net*,struct nlmsghdr*,struct mfcctl*,int*,struct mr_table**,struct netlink_ext_ack*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipmr_rtm_route(struct sk_buff *skb, struct nlmsghdr *nlh,
			  struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	int ret, mrtsock, parent;
	struct mr_table *tbl;
	struct mfcctl mfcc;

	mrtsock = 0;
	tbl = NULL;
	ret = rtm_to_ipmr_mfcc(net, nlh, &mfcc, &mrtsock, &tbl, extack);
	if (ret < 0)
		return ret;

	parent = ret ? mfcc.mfcc_parent : -1;
	if (nlh->nlmsg_type == RTM_NEWROUTE)
		return ipmr_mfc_add(net, tbl, &mfcc, mrtsock, parent);
	else
		return ipmr_mfc_delete(tbl, &mfcc, parent);
}