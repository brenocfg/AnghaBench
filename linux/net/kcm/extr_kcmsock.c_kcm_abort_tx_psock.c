#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_aborts; } ;
struct kcm_psock {int tx_stopped; TYPE_2__* tx_kcm; int /*<<< orphan*/  psock_avail_list; TYPE_1__ stats; struct kcm_mux* mux; struct sock* sk; } ;
struct kcm_mux {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCM_STATS_INCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcm_wq ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_csk_error (struct sock*,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kcm_abort_tx_psock(struct kcm_psock *psock, int err,
			       bool wakeup_kcm)
{
	struct sock *csk = psock->sk;
	struct kcm_mux *mux = psock->mux;

	/* Unrecoverable error in transmit */

	spin_lock_bh(&mux->lock);

	if (psock->tx_stopped) {
		spin_unlock_bh(&mux->lock);
		return;
	}

	psock->tx_stopped = 1;
	KCM_STATS_INCR(psock->stats.tx_aborts);

	if (!psock->tx_kcm) {
		/* Take off psocks_avail list */
		list_del(&psock->psock_avail_list);
	} else if (wakeup_kcm) {
		/* In this case psock is being aborted while outside of
		 * write_msgs and psock is reserved. Schedule tx_work
		 * to handle the failure there. Need to commit tx_stopped
		 * before queuing work.
		 */
		smp_mb();

		queue_work(kcm_wq, &psock->tx_kcm->tx_work);
	}

	spin_unlock_bh(&mux->lock);

	/* Report error on lower socket */
	report_csk_error(csk, err);
}