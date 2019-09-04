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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_trans_txq_scd_cfg {int tid; int aggregate; int /*<<< orphan*/  fifo; int /*<<< orphan*/  frame_limit; int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm_tid_data {int txq_id; scalar_t__ seq_number; int /*<<< orphan*/  deferred_tx_frames; } ;
struct iwl_mvm_sta {size_t reserved_queue; int /*<<< orphan*/  sta_id; TYPE_2__* vif; struct iwl_mvm_tid_data* tid_data; } ;
struct iwl_mvm {TYPE_1__* queue_info; } ;
struct TYPE_4__ {int /*<<< orphan*/ * hw_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 size_t IEEE80211_INVAL_HW_QUEUE ; 
 int /*<<< orphan*/  IEEE80211_SEQ_TO_SN (scalar_t__) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  IWL_FRAME_LIMIT ; 
 int IWL_MAX_TID_COUNT ; 
 int IWL_MVM_DQA_BSS_CLIENT_QUEUE ; 
 int IWL_MVM_DQA_MIN_DATA_QUEUE ; 
 int IWL_MVM_INVALID_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_QUEUE_READY ; 
 int /*<<< orphan*/  IWL_MVM_QUEUE_RESERVED ; 
 int /*<<< orphan*/  iwl_mvm_enable_txq (struct iwl_mvm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_trans_txq_scd_cfg*,unsigned int) ; 
 unsigned int iwl_mvm_get_wd_timeout (struct iwl_mvm*,TYPE_2__*,int,int) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ac_to_tx_fifo (struct iwl_mvm*,int) ; 
 int iwl_mvm_tvqm_enable_txq (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int* tid_to_mac80211_ac ; 

__attribute__((used)) static void iwl_mvm_realloc_queues_after_restart(struct iwl_mvm *mvm,
						 struct iwl_mvm_sta *mvm_sta)
{
	unsigned int wdg_timeout =
			iwl_mvm_get_wd_timeout(mvm, mvm_sta->vif, false, false);
	int i;
	struct iwl_trans_txq_scd_cfg cfg = {
		.sta_id = mvm_sta->sta_id,
		.frame_limit = IWL_FRAME_LIMIT,
	};

	/* Make sure reserved queue is still marked as such (if allocated) */
	if (mvm_sta->reserved_queue != IEEE80211_INVAL_HW_QUEUE)
		mvm->queue_info[mvm_sta->reserved_queue].status =
			IWL_MVM_QUEUE_RESERVED;

	for (i = 0; i <= IWL_MAX_TID_COUNT; i++) {
		struct iwl_mvm_tid_data *tid_data = &mvm_sta->tid_data[i];
		int txq_id = tid_data->txq_id;
		int ac;
		u8 mac_queue;

		if (txq_id == IWL_MVM_INVALID_QUEUE)
			continue;

		skb_queue_head_init(&tid_data->deferred_tx_frames);

		ac = tid_to_mac80211_ac[i];
		mac_queue = mvm_sta->vif->hw_queue[ac];

		if (iwl_mvm_has_new_tx_api(mvm)) {
			IWL_DEBUG_TX_QUEUES(mvm,
					    "Re-mapping sta %d tid %d\n",
					    mvm_sta->sta_id, i);
			txq_id = iwl_mvm_tvqm_enable_txq(mvm, mac_queue,
							 mvm_sta->sta_id,
							 i, wdg_timeout);
			tid_data->txq_id = txq_id;

			/*
			 * Since we don't set the seq number after reset, and HW
			 * sets it now, FW reset will cause the seq num to start
			 * at 0 again, so driver will need to update it
			 * internally as well, so it keeps in sync with real val
			 */
			tid_data->seq_number = 0;
		} else {
			u16 seq = IEEE80211_SEQ_TO_SN(tid_data->seq_number);

			cfg.tid = i;
			cfg.fifo = iwl_mvm_mac_ac_to_tx_fifo(mvm, ac);
			cfg.aggregate = (txq_id >= IWL_MVM_DQA_MIN_DATA_QUEUE ||
					 txq_id ==
					 IWL_MVM_DQA_BSS_CLIENT_QUEUE);

			IWL_DEBUG_TX_QUEUES(mvm,
					    "Re-mapping sta %d tid %d to queue %d\n",
					    mvm_sta->sta_id, i, txq_id);

			iwl_mvm_enable_txq(mvm, txq_id, mac_queue, seq, &cfg,
					   wdg_timeout);
			mvm->queue_info[txq_id].status = IWL_MVM_QUEUE_READY;
		}
	}
}