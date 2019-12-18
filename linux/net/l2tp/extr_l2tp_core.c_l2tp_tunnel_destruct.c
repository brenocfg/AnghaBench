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
struct sock {int /*<<< orphan*/  (* sk_destruct ) (struct sock*) ;int /*<<< orphan*/ * sk_user_data; } ;
struct l2tp_tunnel {int encap; int /*<<< orphan*/  (* old_sk_destruct ) (struct sock*) ;int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * encap_destroy; int /*<<< orphan*/ * encap_rcv; int /*<<< orphan*/  encap_type; } ;

/* Variables and functions */
#define  L2TP_ENCAPTYPE_IP 129 
#define  L2TP_ENCAPTYPE_UDP 128 
 int /*<<< orphan*/  L2TP_MSG_CONTROL ; 
 int /*<<< orphan*/  kfree_rcu (struct l2tp_tunnel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_info (struct l2tp_tunnel*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct l2tp_tunnel* l2tp_tunnel (struct sock*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 TYPE_1__* udp_sk (struct sock*) ; 

__attribute__((used)) static void l2tp_tunnel_destruct(struct sock *sk)
{
	struct l2tp_tunnel *tunnel = l2tp_tunnel(sk);

	if (tunnel == NULL)
		goto end;

	l2tp_info(tunnel, L2TP_MSG_CONTROL, "%s: closing...\n", tunnel->name);

	/* Disable udp encapsulation */
	switch (tunnel->encap) {
	case L2TP_ENCAPTYPE_UDP:
		/* No longer an encapsulation socket. See net/ipv4/udp.c */
		(udp_sk(sk))->encap_type = 0;
		(udp_sk(sk))->encap_rcv = NULL;
		(udp_sk(sk))->encap_destroy = NULL;
		break;
	case L2TP_ENCAPTYPE_IP:
		break;
	}

	/* Remove hooks into tunnel socket */
	sk->sk_destruct = tunnel->old_sk_destruct;
	sk->sk_user_data = NULL;

	/* Call the original destructor */
	if (sk->sk_destruct)
		(*sk->sk_destruct)(sk);

	kfree_rcu(tunnel, rcu);
end:
	return;
}