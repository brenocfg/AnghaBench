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
struct sock {scalar_t__ sk_rcvlowat; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {unsigned int truesize; struct sock* sk; } ;
struct kcm_sock {int /*<<< orphan*/  rx_psock; int /*<<< orphan*/  rx_wait; struct kcm_mux* mux; } ;
struct kcm_mux {int /*<<< orphan*/  rx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcm_rcv_ready (struct kcm_sock*) ; 
 struct kcm_sock* kcm_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,unsigned int) ; 
 scalar_t__ sk_rmem_alloc_get (struct sock*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kcm_rfree(struct sk_buff *skb)
{
	struct sock *sk = skb->sk;
	struct kcm_sock *kcm = kcm_sk(sk);
	struct kcm_mux *mux = kcm->mux;
	unsigned int len = skb->truesize;

	sk_mem_uncharge(sk, len);
	atomic_sub(len, &sk->sk_rmem_alloc);

	/* For reading rx_wait and rx_psock without holding lock */
	smp_mb__after_atomic();

	if (!kcm->rx_wait && !kcm->rx_psock &&
	    sk_rmem_alloc_get(sk) < sk->sk_rcvlowat) {
		spin_lock_bh(&mux->rx_lock);
		kcm_rcv_ready(kcm);
		spin_unlock_bh(&mux->rx_lock);
	}
}