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
struct xfrm_usersa_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct xfrm_state {TYPE_1__ km; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {scalar_t__ nlmsg_type; int /*<<< orphan*/  nlmsg_pid; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct km_event {scalar_t__ event; int /*<<< orphan*/  portid; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 scalar_t__ XFRM_MSG_NEWSA ; 
 scalar_t__ XFRM_STATE_DEAD ; 
 scalar_t__ XFRM_STATE_VALID ; 
 scalar_t__ XFRM_STATE_VOID ; 
 int /*<<< orphan*/  __xfrm_state_put (struct xfrm_state*) ; 
 int /*<<< orphan*/  km_state_notify (struct xfrm_state*,struct km_event*) ; 
 struct xfrm_usersa_info* nlmsg_data (struct nlmsghdr*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int verify_newsa_info (struct xfrm_usersa_info*,struct nlattr**) ; 
 int /*<<< orphan*/  xfrm_audit_state_add (struct xfrm_state*,int,int) ; 
 int /*<<< orphan*/  xfrm_dev_state_delete (struct xfrm_state*) ; 
 int xfrm_state_add (struct xfrm_state*) ; 
 struct xfrm_state* xfrm_state_construct (struct net*,struct xfrm_usersa_info*,struct nlattr**,int*) ; 
 int /*<<< orphan*/  xfrm_state_hold (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 int xfrm_state_update (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_add_sa(struct sk_buff *skb, struct nlmsghdr *nlh,
		struct nlattr **attrs)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_usersa_info *p = nlmsg_data(nlh);
	struct xfrm_state *x;
	int err;
	struct km_event c;

	err = verify_newsa_info(p, attrs);
	if (err)
		return err;

	x = xfrm_state_construct(net, p, attrs, &err);
	if (!x)
		return err;

	xfrm_state_hold(x);
	if (nlh->nlmsg_type == XFRM_MSG_NEWSA)
		err = xfrm_state_add(x);
	else
		err = xfrm_state_update(x);

	xfrm_audit_state_add(x, err ? 0 : 1, true);

	if (err < 0) {
		x->km.state = XFRM_STATE_DEAD;
		xfrm_dev_state_delete(x);
		__xfrm_state_put(x);
		goto out;
	}

	if (x->km.state == XFRM_STATE_VOID)
		x->km.state = XFRM_STATE_VALID;

	c.seq = nlh->nlmsg_seq;
	c.portid = nlh->nlmsg_pid;
	c.event = nlh->nlmsg_type;

	km_state_notify(x, &c);
out:
	xfrm_state_put(x);
	return err;
}