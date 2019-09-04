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
struct TYPE_2__ {int /*<<< orphan*/  sk_receive_queue; } ;
struct kcm_sock {int done; int rx_disabled; TYPE_1__ sk; int /*<<< orphan*/  done_work; int /*<<< orphan*/ * rx_psock; } ;
struct kcm_psock {struct kcm_sock* rx_kcm; struct kcm_mux* mux; } ;
struct kcm_mux {int /*<<< orphan*/  rx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcm_done_work ; 
 int /*<<< orphan*/  kcm_rcv_ready (struct kcm_sock*) ; 
 int /*<<< orphan*/  requeue_rx_msgs (struct kcm_mux*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_rmem_alloc_get (TYPE_1__*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void unreserve_rx_kcm(struct kcm_psock *psock,
			     bool rcv_ready)
{
	struct kcm_sock *kcm = psock->rx_kcm;
	struct kcm_mux *mux = psock->mux;

	if (!kcm)
		return;

	spin_lock_bh(&mux->rx_lock);

	psock->rx_kcm = NULL;
	kcm->rx_psock = NULL;

	/* Commit kcm->rx_psock before sk_rmem_alloc_get to sync with
	 * kcm_rfree
	 */
	smp_mb();

	if (unlikely(kcm->done)) {
		spin_unlock_bh(&mux->rx_lock);

		/* Need to run kcm_done in a task since we need to qcquire
		 * callback locks which may already be held here.
		 */
		INIT_WORK(&kcm->done_work, kcm_done_work);
		schedule_work(&kcm->done_work);
		return;
	}

	if (unlikely(kcm->rx_disabled)) {
		requeue_rx_msgs(mux, &kcm->sk.sk_receive_queue);
	} else if (rcv_ready || unlikely(!sk_rmem_alloc_get(&kcm->sk))) {
		/* Check for degenerative race with rx_wait that all
		 * data was dequeued (accounted for in kcm_rfree).
		 */
		kcm_rcv_ready(kcm);
	}
	spin_unlock_bh(&mux->rx_lock);
}