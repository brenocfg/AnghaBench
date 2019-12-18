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
struct TYPE_2__ {int /*<<< orphan*/  (* getdcbx ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_ATTR_DCBX ; 
 int EOPNOTSUPP ; 
 int nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static int dcbnl_getdcbx(struct net_device *netdev, struct nlmsghdr *nlh,
			 u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	if (!netdev->dcbnl_ops->getdcbx)
		return -EOPNOTSUPP;

	return nla_put_u8(skb, DCB_ATTR_DCBX,
			  netdev->dcbnl_ops->getdcbx(netdev));
}