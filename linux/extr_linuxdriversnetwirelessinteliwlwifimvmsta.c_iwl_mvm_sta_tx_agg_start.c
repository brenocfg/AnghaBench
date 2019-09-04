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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct iwl_mvm_tid_data {scalar_t__ state; int txq_id; size_t ssn; size_t next_reclaimed; int /*<<< orphan*/  seq_number; } ;
struct iwl_mvm_sta {int /*<<< orphan*/  lock; int /*<<< orphan*/  sta_id; struct iwl_mvm_tid_data* tid_data; } ;
struct iwl_mvm {int /*<<< orphan*/  queue_info_lock; TYPE_3__* trans; TYPE_1__* queue_info; int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__* cfg; } ;
struct TYPE_5__ {scalar_t__ gen2; } ;
struct TYPE_4__ {scalar_t__ status; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 size_t IEEE80211_SEQ_TO_SN (int /*<<< orphan*/ ) ; 
 scalar_t__ IWL_AGG_OFF ; 
 scalar_t__ IWL_AGG_QUEUED ; 
 scalar_t__ IWL_AGG_STARTING ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,size_t,...) ; 
 scalar_t__ IWL_EMPTYING_HW_QUEUE_ADDBA ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 size_t IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/  IWL_MVM_DQA_MAX_DATA_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_DQA_MIN_DATA_QUEUE ; 
 int IWL_MVM_INVALID_QUEUE ; 
 scalar_t__ IWL_MVM_QUEUE_RESERVED ; 
 scalar_t__ IWL_MVM_QUEUE_SHARED ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_D0I3 ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee80211_start_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t) ; 
 int iwl_mvm_find_free_queue (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int iwl_mvm_sta_alloc_queue_tvqm (struct iwl_mvm*,struct ieee80211_sta*,int /*<<< orphan*/ ,size_t) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tid_to_mac80211_ac ; 
 scalar_t__ unlikely (int) ; 

int iwl_mvm_sta_tx_agg_start(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			     struct ieee80211_sta *sta, u16 tid, u16 *ssn)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	struct iwl_mvm_tid_data *tid_data;
	u16 normalized_ssn;
	int txq_id;
	int ret;

	if (WARN_ON_ONCE(tid >= IWL_MAX_TID_COUNT))
		return -EINVAL;

	if (mvmsta->tid_data[tid].state != IWL_AGG_QUEUED &&
	    mvmsta->tid_data[tid].state != IWL_AGG_OFF) {
		IWL_ERR(mvm,
			"Start AGG when state is not IWL_AGG_QUEUED or IWL_AGG_OFF %d!\n",
			mvmsta->tid_data[tid].state);
		return -ENXIO;
	}

	lockdep_assert_held(&mvm->mutex);

	if (mvmsta->tid_data[tid].txq_id == IWL_MVM_INVALID_QUEUE &&
	    iwl_mvm_has_new_tx_api(mvm)) {
		u8 ac = tid_to_mac80211_ac[tid];

		ret = iwl_mvm_sta_alloc_queue_tvqm(mvm, sta, ac, tid);
		if (ret)
			return ret;
	}

	spin_lock_bh(&mvmsta->lock);

	/* possible race condition - we entered D0i3 while starting agg */
	if (test_bit(IWL_MVM_STATUS_IN_D0I3, &mvm->status)) {
		spin_unlock_bh(&mvmsta->lock);
		IWL_ERR(mvm, "Entered D0i3 while starting Tx agg\n");
		return -EIO;
	}

	spin_lock(&mvm->queue_info_lock);

	/*
	 * Note the possible cases:
	 *  1. An enabled TXQ - TXQ needs to become agg'ed
	 *  2. The TXQ hasn't yet been enabled, so find a free one and mark
	 *	it as reserved
	 */
	txq_id = mvmsta->tid_data[tid].txq_id;
	if (txq_id == IWL_MVM_INVALID_QUEUE) {
		txq_id = iwl_mvm_find_free_queue(mvm, mvmsta->sta_id,
						 IWL_MVM_DQA_MIN_DATA_QUEUE,
						 IWL_MVM_DQA_MAX_DATA_QUEUE);
		if (txq_id < 0) {
			ret = txq_id;
			IWL_ERR(mvm, "Failed to allocate agg queue\n");
			goto release_locks;
		}

		/* TXQ hasn't yet been enabled, so mark it only as reserved */
		mvm->queue_info[txq_id].status = IWL_MVM_QUEUE_RESERVED;
	} else if (unlikely(mvm->queue_info[txq_id].status ==
			    IWL_MVM_QUEUE_SHARED)) {
		ret = -ENXIO;
		IWL_DEBUG_TX_QUEUES(mvm,
				    "Can't start tid %d agg on shared queue!\n",
				    tid);
		goto release_locks;
	}

	spin_unlock(&mvm->queue_info_lock);

	IWL_DEBUG_TX_QUEUES(mvm,
			    "AGG for tid %d will be on queue #%d\n",
			    tid, txq_id);

	tid_data = &mvmsta->tid_data[tid];
	tid_data->ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);
	tid_data->txq_id = txq_id;
	*ssn = tid_data->ssn;

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Start AGG: sta %d tid %d queue %d - ssn = %d, next_recl = %d\n",
			    mvmsta->sta_id, tid, txq_id, tid_data->ssn,
			    tid_data->next_reclaimed);

	/*
	 * In 22000 HW, the next_reclaimed index is only 8 bit, so we'll need
	 * to align the wrap around of ssn so we compare relevant values.
	 */
	normalized_ssn = tid_data->ssn;
	if (mvm->trans->cfg->gen2)
		normalized_ssn &= 0xff;

	if (normalized_ssn == tid_data->next_reclaimed) {
		tid_data->state = IWL_AGG_STARTING;
		ieee80211_start_tx_ba_cb_irqsafe(vif, sta->addr, tid);
	} else {
		tid_data->state = IWL_EMPTYING_HW_QUEUE_ADDBA;
	}

	ret = 0;
	goto out;

release_locks:
	spin_unlock(&mvm->queue_info_lock);
out:
	spin_unlock_bh(&mvmsta->lock);

	return ret;
}