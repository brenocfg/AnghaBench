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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* dcbnl_ops; } ;
typedef  int /*<<< orphan*/  perm_addr ;
struct TYPE_2__ {int /*<<< orphan*/  (* getpermhwaddr ) (struct net_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_ATTR_PERM_HWADDR ; 
 int EOPNOTSUPP ; 
 int MAX_ADDR_LEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dcbnl_getperm_hwaddr(struct net_device *netdev, struct nlmsghdr *nlh,
				u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	u8 perm_addr[MAX_ADDR_LEN];

	if (!netdev->dcbnl_ops->getpermhwaddr)
		return -EOPNOTSUPP;

	memset(perm_addr, 0, sizeof(perm_addr));
	netdev->dcbnl_ops->getpermhwaddr(netdev, perm_addr);

	return nla_put(skb, DCB_ATTR_PERM_HWADDR, sizeof(perm_addr), perm_addr);
}