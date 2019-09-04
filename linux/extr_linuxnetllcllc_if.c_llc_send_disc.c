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
typedef  int u16 ;
struct sock {scalar_t__ sk_type; scalar_t__ sk_state; } ;
struct sk_buff {int dummy; } ;
struct llc_conn_state_ev {int /*<<< orphan*/  prim_type; int /*<<< orphan*/  prim; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LLC_CONN_EV_TYPE_PRIM ; 
 scalar_t__ LLC_CONN_OUT_OF_SVC ; 
 scalar_t__ LLC_CONN_STATE_ADM ; 
 int /*<<< orphan*/  LLC_DISC_PRIM ; 
 int /*<<< orphan*/  LLC_PRIM_TYPE_REQ ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ TCP_CLOSING ; 
 scalar_t__ TCP_ESTABLISHED ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct llc_conn_state_ev* llc_conn_ev (struct sk_buff*) ; 
 int llc_conn_state_process (struct sock*,struct sk_buff*) ; 
 TYPE_1__* llc_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

int llc_send_disc(struct sock *sk)
{
	u16 rc = 1;
	struct llc_conn_state_ev *ev;
	struct sk_buff *skb;

	sock_hold(sk);
	if (sk->sk_type != SOCK_STREAM || sk->sk_state != TCP_ESTABLISHED ||
	    llc_sk(sk)->state == LLC_CONN_STATE_ADM ||
	    llc_sk(sk)->state == LLC_CONN_OUT_OF_SVC)
		goto out;
	/*
	 * Postpone unassigning the connection from its SAP and returning the
	 * connection until all ACTIONs have been completely executed
	 */
	skb = alloc_skb(0, GFP_ATOMIC);
	if (!skb)
		goto out;
	skb_set_owner_w(skb, sk);
	sk->sk_state  = TCP_CLOSING;
	ev	      = llc_conn_ev(skb);
	ev->type      = LLC_CONN_EV_TYPE_PRIM;
	ev->prim      = LLC_DISC_PRIM;
	ev->prim_type = LLC_PRIM_TYPE_REQ;
	rc = llc_conn_state_process(sk, skb);
out:
	sock_put(sk);
	return rc;
}