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
struct kcm_sock {int tx_wait; struct kcm_psock* tx_psock; struct kcm_mux* mux; } ;
struct TYPE_4__ {int /*<<< orphan*/  unreserved; } ;
struct kcm_psock {TYPE_3__* sk; int /*<<< orphan*/  psock_list; scalar_t__ done; int /*<<< orphan*/  tx_stopped; TYPE_1__ stats; int /*<<< orphan*/ * tx_kcm; } ;
struct kcm_mux {int /*<<< orphan*/  lock; int /*<<< orphan*/  psocks_cnt; } ;
struct TYPE_6__ {TYPE_2__* sk_socket; } ;
struct TYPE_5__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCM_STATS_INCR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcm_psockp ; 
 int /*<<< orphan*/  kcm_update_tx_mux_stats (struct kcm_mux*,struct kcm_psock*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kcm_psock*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psock_now_avail (struct kcm_psock*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  sock_put (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unreserve_psock(struct kcm_sock *kcm)
{
	struct kcm_psock *psock;
	struct kcm_mux *mux = kcm->mux;

	spin_lock_bh(&mux->lock);

	psock = kcm->tx_psock;

	if (WARN_ON(!psock)) {
		spin_unlock_bh(&mux->lock);
		return;
	}

	smp_rmb(); /* Read tx_psock before tx_wait */

	kcm_update_tx_mux_stats(mux, psock);

	WARN_ON(kcm->tx_wait);

	kcm->tx_psock = NULL;
	psock->tx_kcm = NULL;
	KCM_STATS_INCR(psock->stats.unreserved);

	if (unlikely(psock->tx_stopped)) {
		if (psock->done) {
			/* Deferred free */
			list_del(&psock->psock_list);
			mux->psocks_cnt--;
			sock_put(psock->sk);
			fput(psock->sk->sk_socket->file);
			kmem_cache_free(kcm_psockp, psock);
		}

		/* Don't put back on available list */

		spin_unlock_bh(&mux->lock);

		return;
	}

	psock_now_avail(psock);

	spin_unlock_bh(&mux->lock);
}