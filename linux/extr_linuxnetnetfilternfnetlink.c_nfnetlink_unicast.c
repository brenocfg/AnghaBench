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
struct net {int /*<<< orphan*/  nfnl; } ;

/* Variables and functions */
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int) ; 

int nfnetlink_unicast(struct sk_buff *skb, struct net *net, u32 portid,
		      int flags)
{
	return netlink_unicast(net->nfnl, skb, portid, flags);
}