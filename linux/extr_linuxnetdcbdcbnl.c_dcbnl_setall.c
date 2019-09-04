#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* dcbnl_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* setall ) (struct net_device*) ;} ;

/* Variables and functions */
 size_t DCB_ATTR_SET_ALL ; 
 int /*<<< orphan*/  DCB_CMD_SET_ALL ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  RTM_SETDCB ; 
 int /*<<< orphan*/  dcbnl_cee_notify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_put_u8 (struct sk_buff*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static int dcbnl_setall(struct net_device *netdev, struct nlmsghdr *nlh,
			u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	int ret;

	if (!tb[DCB_ATTR_SET_ALL])
		return -EINVAL;

	if (!netdev->dcbnl_ops->setall)
		return -EOPNOTSUPP;

	ret = nla_put_u8(skb, DCB_ATTR_SET_ALL,
			 netdev->dcbnl_ops->setall(netdev));
	dcbnl_cee_notify(netdev, RTM_SETDCB, DCB_CMD_SET_ALL, seq, 0);

	return ret;
}