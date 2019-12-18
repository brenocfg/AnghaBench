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
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;
struct TYPE_2__ {scalar_t__ skb_parser; } ;
struct sk_psock {int /*<<< orphan*/  rcu; TYPE_1__ progs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_PSOCK_TX_ENABLED ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_sk_user_data (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_psock_clear_state (struct sk_psock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_psock_cork_free (struct sk_psock*) ; 
 int /*<<< orphan*/  sk_psock_destroy ; 
 int /*<<< orphan*/  sk_psock_restore_proto (struct sock*,struct sk_psock*) ; 
 int /*<<< orphan*/  sk_psock_stop_strp (struct sock*,struct sk_psock*) ; 
 int /*<<< orphan*/  sk_psock_zap_ingress (struct sk_psock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void sk_psock_drop(struct sock *sk, struct sk_psock *psock)
{
	sk_psock_cork_free(psock);
	sk_psock_zap_ingress(psock);

	write_lock_bh(&sk->sk_callback_lock);
	sk_psock_restore_proto(sk, psock);
	rcu_assign_sk_user_data(sk, NULL);
	if (psock->progs.skb_parser)
		sk_psock_stop_strp(sk, psock);
	write_unlock_bh(&sk->sk_callback_lock);
	sk_psock_clear_state(psock, SK_PSOCK_TX_ENABLED);

	call_rcu(&psock->rcu, sk_psock_destroy);
}