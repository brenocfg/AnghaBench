#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfrm_usersa_info {int dummy; } ;
struct xfrm_usersa_id {int /*<<< orphan*/  proto; int /*<<< orphan*/  family; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  family; } ;
struct xfrm_state {TYPE_2__ id; TYPE_1__ props; } ;
struct xfrm_mark {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct km_event {int /*<<< orphan*/  event; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NLMSG_ALIGN (unsigned int) ; 
 int /*<<< orphan*/  XFRMA_SA ; 
 int /*<<< orphan*/  XFRMNLGRP_SA ; 
 int /*<<< orphan*/  XFRM_MSG_DELSA ; 
 int copy_to_user_state_extra (struct xfrm_state*,struct xfrm_usersa_info*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct xfrm_usersa_id*,int /*<<< orphan*/ ,int) ; 
 struct xfrm_usersa_info* nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_total_size (int) ; 
 void* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (unsigned int,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int xfrm_nlmsg_multicast (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int xfrm_sa_len (struct xfrm_state*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_notify_sa(struct xfrm_state *x, const struct km_event *c)
{
	struct net *net = xs_net(x);
	struct xfrm_usersa_info *p;
	struct xfrm_usersa_id *id;
	struct nlmsghdr *nlh;
	struct sk_buff *skb;
	unsigned int len = xfrm_sa_len(x);
	unsigned int headlen;
	int err;

	headlen = sizeof(*p);
	if (c->event == XFRM_MSG_DELSA) {
		len += nla_total_size(headlen);
		headlen = sizeof(*id);
		len += nla_total_size(sizeof(struct xfrm_mark));
	}
	len += NLMSG_ALIGN(headlen);

	skb = nlmsg_new(len, GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	nlh = nlmsg_put(skb, c->portid, c->seq, c->event, headlen, 0);
	err = -EMSGSIZE;
	if (nlh == NULL)
		goto out_free_skb;

	p = nlmsg_data(nlh);
	if (c->event == XFRM_MSG_DELSA) {
		struct nlattr *attr;

		id = nlmsg_data(nlh);
		memset(id, 0, sizeof(*id));
		memcpy(&id->daddr, &x->id.daddr, sizeof(id->daddr));
		id->spi = x->id.spi;
		id->family = x->props.family;
		id->proto = x->id.proto;

		attr = nla_reserve(skb, XFRMA_SA, sizeof(*p));
		err = -EMSGSIZE;
		if (attr == NULL)
			goto out_free_skb;

		p = nla_data(attr);
	}
	err = copy_to_user_state_extra(x, p, skb);
	if (err)
		goto out_free_skb;

	nlmsg_end(skb, nlh);

	return xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_SA);

out_free_skb:
	kfree_skb(skb);
	return err;
}