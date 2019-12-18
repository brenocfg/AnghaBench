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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int nlmsg_notify (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 

int nfnetlink_send(struct sk_buff *skb, struct net *net, u32 portid,
		   unsigned int group, int echo, gfp_t flags)
{
	return nlmsg_notify(net->nfnl, skb, portid, group, echo, flags);
}