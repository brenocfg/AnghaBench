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
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {struct dcbnl_rtnl_ops* dcbnl_ops; } ;
struct dcbnl_rtnl_ops {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int dcbnl_cee_fill (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static int dcbnl_cee_get(struct net_device *netdev, struct nlmsghdr *nlh,
			 u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	const struct dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;

	if (!ops)
		return -EOPNOTSUPP;

	return dcbnl_cee_fill(skb, netdev);
}