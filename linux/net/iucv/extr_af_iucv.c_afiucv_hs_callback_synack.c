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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct sk_buff {int dummy; } ;
struct iucv_sock {int /*<<< orphan*/  msglimit_peer; } ;
struct TYPE_2__ {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 scalar_t__ IUCV_BOUND ; 
 scalar_t__ IUCV_CONNECTED ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 TYPE_1__* iucv_trans_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int afiucv_hs_callback_synack(struct sock *sk, struct sk_buff *skb)
{
	struct iucv_sock *iucv = iucv_sk(sk);

	if (!iucv)
		goto out;
	if (sk->sk_state != IUCV_BOUND)
		goto out;
	bh_lock_sock(sk);
	iucv->msglimit_peer = iucv_trans_hdr(skb)->window;
	sk->sk_state = IUCV_CONNECTED;
	sk->sk_state_change(sk);
	bh_unlock_sock(sk);
out:
	kfree_skb(skb);
	return NET_RX_SUCCESS;
}