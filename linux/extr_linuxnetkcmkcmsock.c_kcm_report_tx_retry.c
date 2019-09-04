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
struct kcm_sock {struct kcm_mux* mux; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_retries; } ;
struct kcm_mux {int /*<<< orphan*/  lock; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCM_STATS_INCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kcm_report_tx_retry(struct kcm_sock *kcm)
{
	struct kcm_mux *mux = kcm->mux;

	spin_lock_bh(&mux->lock);
	KCM_STATS_INCR(mux->stats.tx_retries);
	spin_unlock_bh(&mux->lock);
}