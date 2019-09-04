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
struct xfrm_policy {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct km_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  XFRMNLGRP_EXPIRE ; 
 int build_polexpire (struct sk_buff*,struct xfrm_policy*,int,struct km_event const*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfrm_nlmsg_multicast (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_polexpire_msgsize (struct xfrm_policy*) ; 
 struct net* xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static int xfrm_exp_policy_notify(struct xfrm_policy *xp, int dir, const struct km_event *c)
{
	struct net *net = xp_net(xp);
	struct sk_buff *skb;
	int err;

	skb = nlmsg_new(xfrm_polexpire_msgsize(xp), GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	err = build_polexpire(skb, xp, dir, c);
	BUG_ON(err < 0);

	return xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_EXPIRE);
}