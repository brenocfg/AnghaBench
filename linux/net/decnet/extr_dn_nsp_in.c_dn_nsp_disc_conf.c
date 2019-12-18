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
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;TYPE_1__* sk_socket; int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct dn_scp {int state; int /*<<< orphan*/  persist; int /*<<< orphan*/  persist_fxn; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
#define  DN_CC 132 
#define  DN_CI 131 
 void* DN_CN ; 
#define  DN_DI 130 
 int DN_DIC ; 
#define  DN_DR 129 
 int DN_DRC ; 
 int DN_NR ; 
#define  DN_RUN 128 
 struct dn_scp* DN_SK (struct sock*) ; 
 unsigned short NSP_REASON_DC ; 
 unsigned short NSP_REASON_NL ; 
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 scalar_t__ SS_DISCONNECTING ; 
 scalar_t__ SS_UNCONNECTED ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  dn_destroy_timer ; 
 int /*<<< orphan*/  dn_nsp_persist (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void dn_nsp_disc_conf(struct sock *sk, struct sk_buff *skb)
{
	struct dn_scp *scp = DN_SK(sk);
	unsigned short reason;

	if (skb->len != 2)
		goto out;

	reason = le16_to_cpu(*(__le16 *)skb->data);

	sk->sk_state = TCP_CLOSE;

	switch (scp->state) {
	case DN_CI:
		scp->state = DN_NR;
		break;
	case DN_DR:
		if (reason == NSP_REASON_DC)
			scp->state = DN_DRC;
		if (reason == NSP_REASON_NL)
			scp->state = DN_CN;
		break;
	case DN_DI:
		scp->state = DN_DIC;
		break;
	case DN_RUN:
		sk->sk_shutdown |= SHUTDOWN_MASK;
		/* fall through */
	case DN_CC:
		scp->state = DN_CN;
	}

	if (!sock_flag(sk, SOCK_DEAD)) {
		if (sk->sk_socket->state != SS_UNCONNECTED)
			sk->sk_socket->state = SS_DISCONNECTING;
		sk->sk_state_change(sk);
	}

	scp->persist_fxn = dn_destroy_timer;
	scp->persist = dn_nsp_persist(sk);

out:
	kfree_skb(skb);
}