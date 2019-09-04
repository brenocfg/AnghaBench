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
struct TYPE_5__ {int /*<<< orphan*/  airtime; int /*<<< orphan*/  pkts; } ;
struct TYPE_4__ {int /*<<< orphan*/  airtime; int /*<<< orphan*/  pkts; } ;
struct iwl_mvm_tcm_mac {TYPE_2__ tx; TYPE_1__ rx; } ;
struct TYPE_6__ {int paused; int /*<<< orphan*/  lock; struct iwl_mvm_tcm_mac* data; void* ll_ts; void* ts; } ;
struct iwl_mvm {TYPE_3__ tcm; } ;

/* Variables and functions */
 int NUM_MAC_INDEX_DRIVER ; 
 void* jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iwl_mvm_resume_tcm(struct iwl_mvm *mvm)
{
	int mac;

	spin_lock_bh(&mvm->tcm.lock);
	mvm->tcm.ts = jiffies;
	mvm->tcm.ll_ts = jiffies;
	for (mac = 0; mac < NUM_MAC_INDEX_DRIVER; mac++) {
		struct iwl_mvm_tcm_mac *mdata = &mvm->tcm.data[mac];

		memset(&mdata->rx.pkts, 0, sizeof(mdata->rx.pkts));
		memset(&mdata->tx.pkts, 0, sizeof(mdata->tx.pkts));
		memset(&mdata->rx.airtime, 0, sizeof(mdata->rx.airtime));
		memset(&mdata->tx.airtime, 0, sizeof(mdata->tx.airtime));
	}
	/* The TCM data needs to be reset before "paused" flag changes */
	smp_mb();
	mvm->tcm.paused = false;
	spin_unlock_bh(&mvm->tcm.lock);
}