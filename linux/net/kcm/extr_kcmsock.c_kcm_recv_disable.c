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
struct kcm_sock {int rx_disabled; int rx_wait; TYPE_1__ sk; int /*<<< orphan*/  wait_rx_list; int /*<<< orphan*/  rx_psock; struct kcm_mux* mux; } ;
struct kcm_mux {int /*<<< orphan*/  rx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  requeue_rx_msgs (struct kcm_mux*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kcm_recv_disable(struct kcm_sock *kcm)
{
	struct kcm_mux *mux = kcm->mux;

	if (kcm->rx_disabled)
		return;

	spin_lock_bh(&mux->rx_lock);

	kcm->rx_disabled = 1;

	/* If a psock is reserved we'll do cleanup in unreserve */
	if (!kcm->rx_psock) {
		if (kcm->rx_wait) {
			list_del(&kcm->wait_rx_list);
			kcm->rx_wait = false;
		}

		requeue_rx_msgs(mux, &kcm->sk.sk_receive_queue);
	}

	spin_unlock_bh(&mux->rx_lock);
}