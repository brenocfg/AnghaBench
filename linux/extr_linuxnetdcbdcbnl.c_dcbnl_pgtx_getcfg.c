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
struct net_device {int dummy; } ;

/* Variables and functions */
 int __dcbnl_pg_getcfg (struct net_device*,struct nlmsghdr*,struct nlattr**,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcbnl_pgtx_getcfg(struct net_device *netdev, struct nlmsghdr *nlh,
			     u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	return __dcbnl_pg_getcfg(netdev, nlh, tb, skb, 0);
}