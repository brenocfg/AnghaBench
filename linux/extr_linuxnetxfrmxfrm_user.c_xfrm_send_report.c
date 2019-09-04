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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_selector {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  XFRMNLGRP_REPORT ; 
 int build_report (struct sk_buff*,int /*<<< orphan*/ ,struct xfrm_selector*,int /*<<< orphan*/ *) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfrm_nlmsg_multicast (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_report_msgsize () ; 

__attribute__((used)) static int xfrm_send_report(struct net *net, u8 proto,
			    struct xfrm_selector *sel, xfrm_address_t *addr)
{
	struct sk_buff *skb;
	int err;

	skb = nlmsg_new(xfrm_report_msgsize(), GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	err = build_report(skb, proto, sel, addr);
	BUG_ON(err < 0);

	return xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_REPORT);
}