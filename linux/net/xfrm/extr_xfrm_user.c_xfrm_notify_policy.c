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
struct xfrm_userpolicy_info {int dummy; } ;
struct xfrm_userpolicy_id {int dir; int /*<<< orphan*/  sel; int /*<<< orphan*/  index; } ;
struct xfrm_user_tmpl {int dummy; } ;
struct xfrm_policy {int xfrm_nr; int /*<<< orphan*/  if_id; int /*<<< orphan*/  mark; int /*<<< orphan*/  type; int /*<<< orphan*/  selector; int /*<<< orphan*/  index; } ;
struct xfrm_mark {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ byid; } ;
struct km_event {TYPE_1__ data; int /*<<< orphan*/  event; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NLMSG_ALIGN (unsigned int) ; 
 int /*<<< orphan*/  XFRMA_POLICY ; 
 int /*<<< orphan*/  XFRMNLGRP_POLICY ; 
 int /*<<< orphan*/  XFRM_MSG_DELPOLICY ; 
 int /*<<< orphan*/  copy_to_user_policy (struct xfrm_policy*,struct xfrm_userpolicy_info*,int) ; 
 int copy_to_user_policy_type (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int copy_to_user_tmpl (struct xfrm_policy*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct xfrm_userpolicy_id*,int /*<<< orphan*/ ,int) ; 
 struct xfrm_userpolicy_info* nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 unsigned int nla_total_size (int) ; 
 void* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (unsigned int,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ userpolicy_type_attrsize () ; 
 int xfrm_if_id_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int xfrm_mark_put (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int xfrm_nlmsg_multicast (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static int xfrm_notify_policy(struct xfrm_policy *xp, int dir, const struct km_event *c)
{
	unsigned int len = nla_total_size(sizeof(struct xfrm_user_tmpl) * xp->xfrm_nr);
	struct net *net = xp_net(xp);
	struct xfrm_userpolicy_info *p;
	struct xfrm_userpolicy_id *id;
	struct nlmsghdr *nlh;
	struct sk_buff *skb;
	unsigned int headlen;
	int err;

	headlen = sizeof(*p);
	if (c->event == XFRM_MSG_DELPOLICY) {
		len += nla_total_size(headlen);
		headlen = sizeof(*id);
	}
	len += userpolicy_type_attrsize();
	len += nla_total_size(sizeof(struct xfrm_mark));
	len += NLMSG_ALIGN(headlen);

	skb = nlmsg_new(len, GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	nlh = nlmsg_put(skb, c->portid, c->seq, c->event, headlen, 0);
	err = -EMSGSIZE;
	if (nlh == NULL)
		goto out_free_skb;

	p = nlmsg_data(nlh);
	if (c->event == XFRM_MSG_DELPOLICY) {
		struct nlattr *attr;

		id = nlmsg_data(nlh);
		memset(id, 0, sizeof(*id));
		id->dir = dir;
		if (c->data.byid)
			id->index = xp->index;
		else
			memcpy(&id->sel, &xp->selector, sizeof(id->sel));

		attr = nla_reserve(skb, XFRMA_POLICY, sizeof(*p));
		err = -EMSGSIZE;
		if (attr == NULL)
			goto out_free_skb;

		p = nla_data(attr);
	}

	copy_to_user_policy(xp, p, dir);
	err = copy_to_user_tmpl(xp, skb);
	if (!err)
		err = copy_to_user_policy_type(xp->type, skb);
	if (!err)
		err = xfrm_mark_put(skb, &xp->mark);
	if (!err)
		err = xfrm_if_id_put(skb, xp->if_id);
	if (err)
		goto out_free_skb;

	nlmsg_end(skb, nlh);

	return xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_POLICY);

out_free_skb:
	kfree_skb(skb);
	return err;
}