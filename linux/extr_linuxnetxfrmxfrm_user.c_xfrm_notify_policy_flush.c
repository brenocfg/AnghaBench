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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct km_event {TYPE_1__ data; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; struct net* net; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  XFRMNLGRP_POLICY ; 
 int /*<<< orphan*/  XFRM_MSG_FLUSHPOLICY ; 
 int copy_to_user_policy_type (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  userpolicy_type_attrsize () ; 
 int xfrm_nlmsg_multicast (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm_notify_policy_flush(const struct km_event *c)
{
	struct net *net = c->net;
	struct nlmsghdr *nlh;
	struct sk_buff *skb;
	int err;

	skb = nlmsg_new(userpolicy_type_attrsize(), GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	nlh = nlmsg_put(skb, c->portid, c->seq, XFRM_MSG_FLUSHPOLICY, 0, 0);
	err = -EMSGSIZE;
	if (nlh == NULL)
		goto out_free_skb;
	err = copy_to_user_policy_type(c->data.type, skb);
	if (err)
		goto out_free_skb;

	nlmsg_end(skb, nlh);

	return xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_POLICY);

out_free_skb:
	kfree_skb(skb);
	return err;
}