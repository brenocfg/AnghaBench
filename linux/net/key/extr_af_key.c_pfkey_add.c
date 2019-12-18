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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct xfrm_state {TYPE_1__ km; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_msg {scalar_t__ sadb_msg_type; int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_seq; } ;
struct net {int dummy; } ;
struct km_event {int /*<<< orphan*/  portid; int /*<<< orphan*/  seq; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct xfrm_state*) ; 
 int PTR_ERR (struct xfrm_state*) ; 
 scalar_t__ SADB_ADD ; 
 int /*<<< orphan*/  XFRM_MSG_NEWSA ; 
 int /*<<< orphan*/  XFRM_MSG_UPDSA ; 
 int /*<<< orphan*/  XFRM_STATE_DEAD ; 
 int /*<<< orphan*/  __xfrm_state_put (struct xfrm_state*) ; 
 int /*<<< orphan*/  km_state_notify (struct xfrm_state*,struct km_event*) ; 
 struct xfrm_state* pfkey_msg2xfrm_state (struct net*,struct sadb_msg const*,void* const*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  xfrm_audit_state_add (struct xfrm_state*,int,int) ; 
 int xfrm_state_add (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_hold (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 int xfrm_state_update (struct xfrm_state*) ; 

__attribute__((used)) static int pfkey_add(struct sock *sk, struct sk_buff *skb, const struct sadb_msg *hdr, void * const *ext_hdrs)
{
	struct net *net = sock_net(sk);
	struct xfrm_state *x;
	int err;
	struct km_event c;

	x = pfkey_msg2xfrm_state(net, hdr, ext_hdrs);
	if (IS_ERR(x))
		return PTR_ERR(x);

	xfrm_state_hold(x);
	if (hdr->sadb_msg_type == SADB_ADD)
		err = xfrm_state_add(x);
	else
		err = xfrm_state_update(x);

	xfrm_audit_state_add(x, err ? 0 : 1, true);

	if (err < 0) {
		x->km.state = XFRM_STATE_DEAD;
		__xfrm_state_put(x);
		goto out;
	}

	if (hdr->sadb_msg_type == SADB_ADD)
		c.event = XFRM_MSG_NEWSA;
	else
		c.event = XFRM_MSG_UPDSA;
	c.seq = hdr->sadb_msg_seq;
	c.portid = hdr->sadb_msg_pid;
	km_state_notify(x, &c);
out:
	xfrm_state_put(x);
	return err;
}