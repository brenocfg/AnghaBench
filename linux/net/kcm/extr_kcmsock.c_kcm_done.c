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
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct kcm_sock {int done; int rx_disabled; int rx_wait; struct sock sk; int /*<<< orphan*/  kcm_sock_list; int /*<<< orphan*/  wait_rx_list; scalar_t__ rx_psock; struct kcm_mux* mux; } ;
struct kcm_mux {int kcm_socks_cnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_lock; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mux (struct kcm_mux*) ; 
 int /*<<< orphan*/  requeue_rx_msgs (struct kcm_mux*,int /*<<< orphan*/ *) ; 
 int sk_rmem_alloc_get (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kcm_done(struct kcm_sock *kcm)
{
	struct kcm_mux *mux = kcm->mux;
	struct sock *sk = &kcm->sk;
	int socks_cnt;

	spin_lock_bh(&mux->rx_lock);
	if (kcm->rx_psock) {
		/* Cleanup in unreserve_rx_kcm */
		WARN_ON(kcm->done);
		kcm->rx_disabled = 1;
		kcm->done = 1;
		spin_unlock_bh(&mux->rx_lock);
		return;
	}

	if (kcm->rx_wait) {
		list_del(&kcm->wait_rx_list);
		kcm->rx_wait = false;
	}
	/* Move any pending receive messages to other kcm sockets */
	requeue_rx_msgs(mux, &sk->sk_receive_queue);

	spin_unlock_bh(&mux->rx_lock);

	if (WARN_ON(sk_rmem_alloc_get(sk)))
		return;

	/* Detach from MUX */
	spin_lock_bh(&mux->lock);

	list_del(&kcm->kcm_sock_list);
	mux->kcm_socks_cnt--;
	socks_cnt = mux->kcm_socks_cnt;

	spin_unlock_bh(&mux->lock);

	if (!socks_cnt) {
		/* We are done with the mux now. */
		release_mux(mux);
	}

	WARN_ON(kcm->rx_wait);

	sock_put(&kcm->sk);
}