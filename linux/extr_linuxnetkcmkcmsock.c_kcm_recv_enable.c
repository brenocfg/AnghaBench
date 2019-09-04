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
struct kcm_sock {scalar_t__ rx_disabled; struct kcm_mux* mux; } ;
struct kcm_mux {int /*<<< orphan*/  rx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kcm_rcv_ready (struct kcm_sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kcm_recv_enable(struct kcm_sock *kcm)
{
	struct kcm_mux *mux = kcm->mux;

	if (!kcm->rx_disabled)
		return;

	spin_lock_bh(&mux->rx_lock);

	kcm->rx_disabled = 0;
	kcm_rcv_ready(kcm);

	spin_unlock_bh(&mux->rx_lock);
}