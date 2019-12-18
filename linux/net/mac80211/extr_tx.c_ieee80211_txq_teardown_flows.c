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
struct fq {int /*<<< orphan*/  lock; } ;
struct ieee80211_local {int /*<<< orphan*/ * cvars; TYPE_1__* ops; struct fq fq; } ;
struct TYPE_2__ {int /*<<< orphan*/  wake_tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  fq_reset (struct fq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_skb_free_func ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ieee80211_txq_teardown_flows(struct ieee80211_local *local)
{
	struct fq *fq = &local->fq;

	if (!local->ops->wake_tx_queue)
		return;

	kfree(local->cvars);
	local->cvars = NULL;

	spin_lock_bh(&fq->lock);
	fq_reset(fq, fq_skb_free_func);
	spin_unlock_bh(&fq->lock);
}