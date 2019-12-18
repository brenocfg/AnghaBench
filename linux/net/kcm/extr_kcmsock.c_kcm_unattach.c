#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {TYPE_3__* sk_socket; int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/ * sk_user_data; } ;
struct kcm_psock {int done; int /*<<< orphan*/  psock_list; int /*<<< orphan*/  psock_avail_list; int /*<<< orphan*/  tx_stopped; TYPE_2__* tx_kcm; int /*<<< orphan*/  strp; int /*<<< orphan*/  stats; int /*<<< orphan*/  bpf_prog; int /*<<< orphan*/ * ready_rx_msg; int /*<<< orphan*/  psock_ready_list; int /*<<< orphan*/  rx_kcm; int /*<<< orphan*/  save_state_change; int /*<<< orphan*/  save_write_space; int /*<<< orphan*/  save_data_ready; struct kcm_mux* mux; struct sock* sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  psock_unattach_rsvd; int /*<<< orphan*/  psock_unattach; int /*<<< orphan*/  rx_ready_drops; } ;
struct kcm_mux {int /*<<< orphan*/  lock; int /*<<< orphan*/  psocks_cnt; TYPE_1__ stats; int /*<<< orphan*/  aggregate_strp_stats; int /*<<< orphan*/  aggregate_psock_stats; int /*<<< orphan*/  rx_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  file; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  KCM_STATS_INCR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aggregate_psock_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_prog_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcm_abort_tx_psock (struct kcm_psock*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kcm_psockp ; 
 int /*<<< orphan*/  kcm_wq ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kcm_psock*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  save_strp_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strp_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strp_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kcm_unattach(struct kcm_psock *psock)
{
	struct sock *csk = psock->sk;
	struct kcm_mux *mux = psock->mux;

	lock_sock(csk);

	/* Stop getting callbacks from TCP socket. After this there should
	 * be no way to reserve a kcm for this psock.
	 */
	write_lock_bh(&csk->sk_callback_lock);
	csk->sk_user_data = NULL;
	csk->sk_data_ready = psock->save_data_ready;
	csk->sk_write_space = psock->save_write_space;
	csk->sk_state_change = psock->save_state_change;
	strp_stop(&psock->strp);

	if (WARN_ON(psock->rx_kcm)) {
		write_unlock_bh(&csk->sk_callback_lock);
		release_sock(csk);
		return;
	}

	spin_lock_bh(&mux->rx_lock);

	/* Stop receiver activities. After this point psock should not be
	 * able to get onto ready list either through callbacks or work.
	 */
	if (psock->ready_rx_msg) {
		list_del(&psock->psock_ready_list);
		kfree_skb(psock->ready_rx_msg);
		psock->ready_rx_msg = NULL;
		KCM_STATS_INCR(mux->stats.rx_ready_drops);
	}

	spin_unlock_bh(&mux->rx_lock);

	write_unlock_bh(&csk->sk_callback_lock);

	/* Call strp_done without sock lock */
	release_sock(csk);
	strp_done(&psock->strp);
	lock_sock(csk);

	bpf_prog_put(psock->bpf_prog);

	spin_lock_bh(&mux->lock);

	aggregate_psock_stats(&psock->stats, &mux->aggregate_psock_stats);
	save_strp_stats(&psock->strp, &mux->aggregate_strp_stats);

	KCM_STATS_INCR(mux->stats.psock_unattach);

	if (psock->tx_kcm) {
		/* psock was reserved.  Just mark it finished and we will clean
		 * up in the kcm paths, we need kcm lock which can not be
		 * acquired here.
		 */
		KCM_STATS_INCR(mux->stats.psock_unattach_rsvd);
		spin_unlock_bh(&mux->lock);

		/* We are unattaching a socket that is reserved. Abort the
		 * socket since we may be out of sync in sending on it. We need
		 * to do this without the mux lock.
		 */
		kcm_abort_tx_psock(psock, EPIPE, false);

		spin_lock_bh(&mux->lock);
		if (!psock->tx_kcm) {
			/* psock now unreserved in window mux was unlocked */
			goto no_reserved;
		}
		psock->done = 1;

		/* Commit done before queuing work to process it */
		smp_mb();

		/* Queue tx work to make sure psock->done is handled */
		queue_work(kcm_wq, &psock->tx_kcm->tx_work);
		spin_unlock_bh(&mux->lock);
	} else {
no_reserved:
		if (!psock->tx_stopped)
			list_del(&psock->psock_avail_list);
		list_del(&psock->psock_list);
		mux->psocks_cnt--;
		spin_unlock_bh(&mux->lock);

		sock_put(csk);
		fput(csk->sk_socket->file);
		kmem_cache_free(kcm_psockp, psock);
	}

	release_sock(csk);
}