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
typedef  size_t u8 ;
struct iwl_trans_txq_scd_cfg {int tid; int aggregate; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  frame_limit; int /*<<< orphan*/  fifo; } ;
struct iwl_mvm_sta {unsigned long tfd_queue_msk; size_t reserved_queue; int /*<<< orphan*/  lock; TYPE_2__* tid_data; int /*<<< orphan*/  sta_id; TYPE_3__* vif; } ;
struct iwl_mvm {int /*<<< orphan*/  trans; int /*<<< orphan*/  queue_info_lock; TYPE_1__* queue_info; int /*<<< orphan*/  mutex; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  frame_control; } ;
typedef  enum iwl_mvm_agg_state { ____Placeholder_iwl_mvm_agg_state } iwl_mvm_agg_state ;
struct TYPE_6__ {size_t* hw_queue; } ;
struct TYPE_5__ {int seq_number; int txq_id; int is_tid_active; int state; } ;
struct TYPE_4__ {scalar_t__ status; int reserved; int /*<<< orphan*/  ra_sta_id; } ;

/* Variables and functions */
 unsigned long BIT (int) ; 
 size_t IEEE80211_INVAL_HW_QUEUE ; 
 int IEEE80211_SCTL_SEQ ; 
 int IEEE80211_SEQ_TO_SN (int /*<<< orphan*/ ) ; 
 int IWL_AGG_ON ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_FRAME_LIMIT ; 
 int IWL_MVM_DQA_BSS_CLIENT_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_DQA_MAX_DATA_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_DQA_MAX_MGMT_QUEUE ; 
 int IWL_MVM_DQA_MIN_DATA_QUEUE ; 
 int IWL_MVM_DQA_MIN_MGMT_QUEUE ; 
 scalar_t__ IWL_MVM_QUEUE_INACTIVE ; 
 scalar_t__ IWL_MVM_QUEUE_READY ; 
 scalar_t__ IWL_MVM_QUEUE_RESERVED ; 
 scalar_t__ IWL_MVM_QUEUE_SHARED ; 
 int /*<<< orphan*/  STA_MODIFY_QUEUES ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_qos_nullfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_disable_txq (struct iwl_mvm*,int,size_t,int,int /*<<< orphan*/ ) ; 
 int iwl_mvm_enable_txq (struct iwl_mvm*,int,size_t,int,struct iwl_trans_txq_scd_cfg*,unsigned int) ; 
 int iwl_mvm_find_free_queue (struct iwl_mvm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int iwl_mvm_free_inactive_queue (struct iwl_mvm*,int,int) ; 
 unsigned long iwl_mvm_get_queue_agg_tids (struct iwl_mvm*,int) ; 
 int iwl_mvm_get_shared_queue (struct iwl_mvm*,unsigned long,size_t) ; 
 unsigned int iwl_mvm_get_wd_timeout (struct iwl_mvm*,TYPE_3__*,int,int) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_invalidate_sta_queue (struct iwl_mvm*,int,unsigned long,int) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ac_to_tx_fifo (struct iwl_mvm*,size_t) ; 
 int iwl_mvm_scd_queue_redirect (struct iwl_mvm*,int,int,size_t,int,unsigned int,int) ; 
 int iwl_mvm_sta_alloc_queue_tvqm (struct iwl_mvm*,struct ieee80211_sta*,size_t,int) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int iwl_mvm_sta_send_to_fw (struct iwl_mvm*,struct ieee80211_sta*,int,int /*<<< orphan*/ ) ; 
 int iwl_mvm_sta_tx_agg (struct iwl_mvm*,struct ieee80211_sta*,int,int,int) ; 
 int /*<<< orphan*/  iwl_trans_txq_set_shared_mode (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_sta_alloc_queue(struct iwl_mvm *mvm,
				   struct ieee80211_sta *sta, u8 ac, int tid,
				   struct ieee80211_hdr *hdr)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	struct iwl_trans_txq_scd_cfg cfg = {
		.fifo = iwl_mvm_mac_ac_to_tx_fifo(mvm, ac),
		.sta_id = mvmsta->sta_id,
		.tid = tid,
		.frame_limit = IWL_FRAME_LIMIT,
	};
	unsigned int wdg_timeout =
		iwl_mvm_get_wd_timeout(mvm, mvmsta->vif, false, false);
	u8 mac_queue = mvmsta->vif->hw_queue[ac];
	int queue = -1;
	bool using_inactive_queue = false, same_sta = false;
	unsigned long disable_agg_tids = 0;
	enum iwl_mvm_agg_state queue_state;
	bool shared_queue = false, inc_ssn;
	int ssn;
	unsigned long tfd_queue_mask;
	int ret;

	lockdep_assert_held(&mvm->mutex);

	if (iwl_mvm_has_new_tx_api(mvm))
		return iwl_mvm_sta_alloc_queue_tvqm(mvm, sta, ac, tid);

	spin_lock_bh(&mvmsta->lock);
	tfd_queue_mask = mvmsta->tfd_queue_msk;
	spin_unlock_bh(&mvmsta->lock);

	spin_lock_bh(&mvm->queue_info_lock);

	/*
	 * Non-QoS, QoS NDP and MGMT frames should go to a MGMT queue, if one
	 * exists
	 */
	if (!ieee80211_is_data_qos(hdr->frame_control) ||
	    ieee80211_is_qos_nullfunc(hdr->frame_control)) {
		queue = iwl_mvm_find_free_queue(mvm, mvmsta->sta_id,
						IWL_MVM_DQA_MIN_MGMT_QUEUE,
						IWL_MVM_DQA_MAX_MGMT_QUEUE);
		if (queue >= IWL_MVM_DQA_MIN_MGMT_QUEUE)
			IWL_DEBUG_TX_QUEUES(mvm, "Found free MGMT queue #%d\n",
					    queue);

		/* If no such queue is found, we'll use a DATA queue instead */
	}

	if ((queue < 0 && mvmsta->reserved_queue != IEEE80211_INVAL_HW_QUEUE) &&
	    (mvm->queue_info[mvmsta->reserved_queue].status ==
	     IWL_MVM_QUEUE_RESERVED ||
	     mvm->queue_info[mvmsta->reserved_queue].status ==
	     IWL_MVM_QUEUE_INACTIVE)) {
		queue = mvmsta->reserved_queue;
		mvm->queue_info[queue].reserved = true;
		IWL_DEBUG_TX_QUEUES(mvm, "Using reserved queue #%d\n", queue);
	}

	if (queue < 0)
		queue = iwl_mvm_find_free_queue(mvm, mvmsta->sta_id,
						IWL_MVM_DQA_MIN_DATA_QUEUE,
						IWL_MVM_DQA_MAX_DATA_QUEUE);

	/*
	 * Check if this queue is already allocated but inactive.
	 * In such a case, we'll need to first free this queue before enabling
	 * it again, so we'll mark it as reserved to make sure no new traffic
	 * arrives on it
	 */
	if (queue > 0 &&
	    mvm->queue_info[queue].status == IWL_MVM_QUEUE_INACTIVE) {
		mvm->queue_info[queue].status = IWL_MVM_QUEUE_RESERVED;
		using_inactive_queue = true;
		same_sta = mvm->queue_info[queue].ra_sta_id == mvmsta->sta_id;
		IWL_DEBUG_TX_QUEUES(mvm,
				    "Re-assigning TXQ %d: sta_id=%d, tid=%d\n",
				    queue, mvmsta->sta_id, tid);
	}

	/* No free queue - we'll have to share */
	if (queue <= 0) {
		queue = iwl_mvm_get_shared_queue(mvm, tfd_queue_mask, ac);
		if (queue > 0) {
			shared_queue = true;
			mvm->queue_info[queue].status = IWL_MVM_QUEUE_SHARED;
		}
	}

	/*
	 * Mark TXQ as ready, even though it hasn't been fully configured yet,
	 * to make sure no one else takes it.
	 * This will allow avoiding re-acquiring the lock at the end of the
	 * configuration. On error we'll mark it back as free.
	 */
	if ((queue > 0) && !shared_queue)
		mvm->queue_info[queue].status = IWL_MVM_QUEUE_READY;

	spin_unlock_bh(&mvm->queue_info_lock);

	/* This shouldn't happen - out of queues */
	if (WARN_ON(queue <= 0)) {
		IWL_ERR(mvm, "No available queues for tid %d on sta_id %d\n",
			tid, cfg.sta_id);
		return queue;
	}

	/*
	 * Actual en/disablement of aggregations is through the ADD_STA HCMD,
	 * but for configuring the SCD to send A-MPDUs we need to mark the queue
	 * as aggregatable.
	 * Mark all DATA queues as allowing to be aggregated at some point
	 */
	cfg.aggregate = (queue >= IWL_MVM_DQA_MIN_DATA_QUEUE ||
			 queue == IWL_MVM_DQA_BSS_CLIENT_QUEUE);

	/*
	 * If this queue was previously inactive (idle) - we need to free it
	 * first
	 */
	if (using_inactive_queue) {
		ret = iwl_mvm_free_inactive_queue(mvm, queue, same_sta);
		if (ret)
			return ret;
	}

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Allocating %squeue #%d to sta %d on tid %d\n",
			    shared_queue ? "shared " : "", queue,
			    mvmsta->sta_id, tid);

	if (shared_queue) {
		/* Disable any open aggs on this queue */
		disable_agg_tids = iwl_mvm_get_queue_agg_tids(mvm, queue);

		if (disable_agg_tids) {
			IWL_DEBUG_TX_QUEUES(mvm, "Disabling aggs on queue %d\n",
					    queue);
			iwl_mvm_invalidate_sta_queue(mvm, queue,
						     disable_agg_tids, false);
		}
	}

	ssn = IEEE80211_SEQ_TO_SN(le16_to_cpu(hdr->seq_ctrl));
	inc_ssn = iwl_mvm_enable_txq(mvm, queue, mac_queue,
				     ssn, &cfg, wdg_timeout);
	if (inc_ssn) {
		ssn = (ssn + 1) & IEEE80211_SCTL_SEQ;
		le16_add_cpu(&hdr->seq_ctrl, 0x10);
	}

	/*
	 * Mark queue as shared in transport if shared
	 * Note this has to be done after queue enablement because enablement
	 * can also set this value, and there is no indication there to shared
	 * queues
	 */
	if (shared_queue)
		iwl_trans_txq_set_shared_mode(mvm->trans, queue, true);

	spin_lock_bh(&mvmsta->lock);
	/*
	 * This looks racy, but it is not. We have only one packet for
	 * this ra/tid in our Tx path since we stop the Qdisc when we
	 * need to allocate a new TFD queue.
	 */
	if (inc_ssn)
		mvmsta->tid_data[tid].seq_number += 0x10;
	mvmsta->tid_data[tid].txq_id = queue;
	mvmsta->tid_data[tid].is_tid_active = true;
	mvmsta->tfd_queue_msk |= BIT(queue);
	queue_state = mvmsta->tid_data[tid].state;

	if (mvmsta->reserved_queue == queue)
		mvmsta->reserved_queue = IEEE80211_INVAL_HW_QUEUE;
	spin_unlock_bh(&mvmsta->lock);

	if (!shared_queue) {
		ret = iwl_mvm_sta_send_to_fw(mvm, sta, true, STA_MODIFY_QUEUES);
		if (ret)
			goto out_err;

		/* If we need to re-enable aggregations... */
		if (queue_state == IWL_AGG_ON) {
			ret = iwl_mvm_sta_tx_agg(mvm, sta, tid, queue, true);
			if (ret)
				goto out_err;
		}
	} else {
		/* Redirect queue, if needed */
		ret = iwl_mvm_scd_queue_redirect(mvm, queue, tid, ac, ssn,
						 wdg_timeout, false);
		if (ret)
			goto out_err;
	}

	return 0;

out_err:
	iwl_mvm_disable_txq(mvm, queue, mac_queue, tid, 0);

	return ret;
}