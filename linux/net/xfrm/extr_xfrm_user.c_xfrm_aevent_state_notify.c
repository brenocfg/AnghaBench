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
struct xfrm_state {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct km_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  XFRMNLGRP_AEVENTS ; 
 int build_aevent (struct sk_buff*,struct xfrm_state*,struct km_event const*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_aevent_msgsize (struct xfrm_state*) ; 
 int xfrm_nlmsg_multicast (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_aevent_state_notify(struct xfrm_state *x, const struct km_event *c)
{
	struct net *net = xs_net(x);
	struct sk_buff *skb;
	int err;

	skb = nlmsg_new(xfrm_aevent_msgsize(x), GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	err = build_aevent(skb, x, c);
	BUG_ON(err < 0);

	return xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_AEVENTS);
}