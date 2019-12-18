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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct l2tp_tunnel {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2TP_MSG_DATA ; 
 int /*<<< orphan*/  l2tp_dbg (struct l2tp_tunnel*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ l2tp_udp_recv_core (struct l2tp_tunnel*,struct sk_buff*) ; 
 struct l2tp_tunnel* rcu_dereference_sk_user_data (struct sock*) ; 

int l2tp_udp_encap_recv(struct sock *sk, struct sk_buff *skb)
{
	struct l2tp_tunnel *tunnel;

	tunnel = rcu_dereference_sk_user_data(sk);
	if (tunnel == NULL)
		goto pass_up;

	l2tp_dbg(tunnel, L2TP_MSG_DATA, "%s: received %d bytes\n",
		 tunnel->name, skb->len);

	if (l2tp_udp_recv_core(tunnel, skb))
		goto pass_up;

	return 0;

pass_up:
	return 1;
}