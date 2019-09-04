#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_usersa_id {int /*<<< orphan*/  family; int /*<<< orphan*/  proto; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct xfrm_state {int /*<<< orphan*/  lock; } ;
struct xfrm_mark {int dummy; } ;
struct xfrm_aevent_id {int /*<<< orphan*/  flags; struct xfrm_usersa_id sa_id; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_pid; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  nlsk; } ;
struct net {TYPE_2__ xfrm; } ;
struct TYPE_4__ {int /*<<< orphan*/  aevent; } ;
struct km_event {int /*<<< orphan*/  portid; int /*<<< orphan*/  seq; TYPE_1__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_3__ NETLINK_CB (struct sk_buff*) ; 
 int build_aevent (struct sk_buff*,struct xfrm_state*,struct km_event*) ; 
 struct xfrm_aevent_id* nlmsg_data (struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_aevent_msgsize (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_mark_get (struct nlattr**,struct xfrm_mark*) ; 
 struct xfrm_state* xfrm_state_lookup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_get_ae(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_state *x;
	struct sk_buff *r_skb;
	int err;
	struct km_event c;
	u32 mark;
	struct xfrm_mark m;
	struct xfrm_aevent_id *p = nlmsg_data(nlh);
	struct xfrm_usersa_id *id = &p->sa_id;

	mark = xfrm_mark_get(attrs, &m);

	x = xfrm_state_lookup(net, mark, &id->daddr, id->spi, id->proto, id->family);
	if (x == NULL)
		return -ESRCH;

	r_skb = nlmsg_new(xfrm_aevent_msgsize(x), GFP_ATOMIC);
	if (r_skb == NULL) {
		xfrm_state_put(x);
		return -ENOMEM;
	}

	/*
	 * XXX: is this lock really needed - none of the other
	 * gets lock (the concern is things getting updated
	 * while we are still reading) - jhs
	*/
	spin_lock_bh(&x->lock);
	c.data.aevent = p->flags;
	c.seq = nlh->nlmsg_seq;
	c.portid = nlh->nlmsg_pid;

	err = build_aevent(r_skb, x, &c);
	BUG_ON(err < 0);

	err = nlmsg_unicast(net->xfrm.nlsk, r_skb, NETLINK_CB(skb).portid);
	spin_unlock_bh(&x->lock);
	xfrm_state_put(x);
	return err;
}