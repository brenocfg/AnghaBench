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
typedef  size_t u16 ;
struct sk_buff {scalar_t__ data; } ;
struct iwl_tx_cmd {TYPE_1__* hdr; } ;
struct iwl_mvm_sta {scalar_t__ sta_id; int /*<<< orphan*/  lock; TYPE_3__* tid_data; } ;
struct iwl_mvm {int /*<<< orphan*/  trans; int /*<<< orphan*/  add_stream_wk; TYPE_2__* queue_info; int /*<<< orphan*/  queue_info_lock; } ;
struct iwl_device_cmd {scalar_t__ payload; } ;
struct ieee80211_tx_info {size_t hw_queue; int flags; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {scalar_t__ state; size_t seq_number; size_t txq_id; int is_tid_active; } ;
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/ * last_frame_time; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq_ctrl; } ;

/* Variables and functions */
 size_t IEEE80211_SCTL_FRAG ; 
 size_t IEEE80211_SCTL_SEQ ; 
 int /*<<< orphan*/  IEEE80211_SEQ_TO_SN (size_t) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_SEND_AFTER_DTIM ; 
 int IEEE80211_TX_STATUS_EOSP ; 
 scalar_t__ IWL_AGG_ON ; 
 int /*<<< orphan*/  IWL_DEBUG_TX (struct iwl_mvm*,char*,scalar_t__,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,size_t) ; 
 size_t IWL_MAX_TID_COUNT ; 
 size_t IWL_MVM_INVALID_QUEUE ; 
 scalar_t__ IWL_MVM_INVALID_STA ; 
 scalar_t__ IWL_MVM_QUEUE_READY ; 
 scalar_t__ IWL_MVM_QUEUE_SHARED ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 size_t ieee80211_get_tid (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_has_morefrags (int /*<<< orphan*/ ) ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_qos_nullfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 struct iwl_device_cmd* iwl_mvm_set_tx_params (struct iwl_mvm*,struct sk_buff*,struct ieee80211_tx_info*,int,struct ieee80211_sta*,scalar_t__) ; 
 int /*<<< orphan*/  iwl_mvm_skb_prepare_status (struct sk_buff*,struct iwl_device_cmd*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_tx_add_stream (struct iwl_mvm*,struct iwl_mvm_sta*,size_t,struct sk_buff*) ; 
 int /*<<< orphan*/  iwl_mvm_tx_pkt_queued (struct iwl_mvm*,struct iwl_mvm_sta*,size_t) ; 
 scalar_t__ iwl_mvm_txq_should_update (struct iwl_mvm*,size_t) ; 
 int /*<<< orphan*/  iwl_trans_free_tx_cmd (int /*<<< orphan*/ ,struct iwl_device_cmd*) ; 
 scalar_t__ iwl_trans_tx (int /*<<< orphan*/ ,struct sk_buff*,struct iwl_device_cmd*,size_t) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int iwl_mvm_tx_mpdu(struct iwl_mvm *mvm, struct sk_buff *skb,
			   struct ieee80211_tx_info *info,
			   struct ieee80211_sta *sta)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct iwl_mvm_sta *mvmsta;
	struct iwl_device_cmd *dev_cmd;
	__le16 fc;
	u16 seq_number = 0;
	u8 tid = IWL_MAX_TID_COUNT;
	u16 txq_id = info->hw_queue;
	bool is_ampdu = false;
	int hdrlen;

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	fc = hdr->frame_control;
	hdrlen = ieee80211_hdrlen(fc);

	if (WARN_ON_ONCE(!mvmsta))
		return -1;

	if (WARN_ON_ONCE(mvmsta->sta_id == IWL_MVM_INVALID_STA))
		return -1;

	dev_cmd = iwl_mvm_set_tx_params(mvm, skb, info, hdrlen,
					sta, mvmsta->sta_id);
	if (!dev_cmd)
		goto drop;

	/*
	 * we handle that entirely ourselves -- for uAPSD the firmware
	 * will always send a notification, and for PS-Poll responses
	 * we'll notify mac80211 when getting frame status
	 */
	info->flags &= ~IEEE80211_TX_STATUS_EOSP;

	spin_lock(&mvmsta->lock);

	/* nullfunc frames should go to the MGMT queue regardless of QOS,
	 * the condition of !ieee80211_is_qos_nullfunc(fc) keeps the default
	 * assignment of MGMT TID
	 */
	if (ieee80211_is_data_qos(fc) && !ieee80211_is_qos_nullfunc(fc)) {
		tid = ieee80211_get_tid(hdr);
		if (WARN_ON_ONCE(tid >= IWL_MAX_TID_COUNT))
			goto drop_unlock_sta;

		is_ampdu = info->flags & IEEE80211_TX_CTL_AMPDU;
		if (WARN_ON_ONCE(is_ampdu &&
				 mvmsta->tid_data[tid].state != IWL_AGG_ON))
			goto drop_unlock_sta;

		seq_number = mvmsta->tid_data[tid].seq_number;
		seq_number &= IEEE80211_SCTL_SEQ;

		if (!iwl_mvm_has_new_tx_api(mvm)) {
			struct iwl_tx_cmd *tx_cmd = (void *)dev_cmd->payload;

			hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
			hdr->seq_ctrl |= cpu_to_le16(seq_number);
			/* update the tx_cmd hdr as it was already copied */
			tx_cmd->hdr->seq_ctrl = hdr->seq_ctrl;
		}
	}

	txq_id = mvmsta->tid_data[tid].txq_id;

	WARN_ON_ONCE(info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM);

	/* Check if TXQ needs to be allocated or re-activated */
	if (unlikely(txq_id == IWL_MVM_INVALID_QUEUE ||
		     !mvmsta->tid_data[tid].is_tid_active)) {
		/* If TXQ needs to be allocated... */
		if (txq_id == IWL_MVM_INVALID_QUEUE) {
			iwl_mvm_tx_add_stream(mvm, mvmsta, tid, skb);

			/*
			 * The frame is now deferred, and the worker scheduled
			 * will re-allocate it, so we can free it for now.
			 */
			iwl_trans_free_tx_cmd(mvm->trans, dev_cmd);
			spin_unlock(&mvmsta->lock);
			return 0;
		}

		/* queue should always be active in new TX path */
		WARN_ON(iwl_mvm_has_new_tx_api(mvm));

		/* If we are here - TXQ exists and needs to be re-activated */
		spin_lock(&mvm->queue_info_lock);
		mvm->queue_info[txq_id].status = IWL_MVM_QUEUE_READY;
		mvmsta->tid_data[tid].is_tid_active = true;
		spin_unlock(&mvm->queue_info_lock);

		IWL_DEBUG_TX_QUEUES(mvm, "Re-activating queue %d for TX\n",
				    txq_id);
	}

	if (!iwl_mvm_has_new_tx_api(mvm)) {
		/* Keep track of the time of the last frame for this RA/TID */
		mvm->queue_info[txq_id].last_frame_time[tid] = jiffies;

		/*
		 * If we have timed-out TIDs - schedule the worker that will
		 * reconfig the queues and update them
		 *
		 * Note that the mvm->queue_info_lock isn't being taken here in
		 * order to not serialize the TX flow. This isn't dangerous
		 * because scheduling mvm->add_stream_wk can't ruin the state,
		 * and if we DON'T schedule it due to some race condition then
		 * next TX we get here we will.
		 */
		if (unlikely(mvm->queue_info[txq_id].status ==
			     IWL_MVM_QUEUE_SHARED &&
			     iwl_mvm_txq_should_update(mvm, txq_id)))
			schedule_work(&mvm->add_stream_wk);
	}

	IWL_DEBUG_TX(mvm, "TX to [%d|%d] Q:%d - seq: 0x%x\n", mvmsta->sta_id,
		     tid, txq_id, IEEE80211_SEQ_TO_SN(seq_number));

	/* From now on, we cannot access info->control */
	iwl_mvm_skb_prepare_status(skb, dev_cmd);

	if (iwl_trans_tx(mvm->trans, skb, dev_cmd, txq_id))
		goto drop_unlock_sta;

	if (tid < IWL_MAX_TID_COUNT && !ieee80211_has_morefrags(fc))
		mvmsta->tid_data[tid].seq_number = seq_number + 0x10;

	spin_unlock(&mvmsta->lock);

	iwl_mvm_tx_pkt_queued(mvm, mvmsta, tid == IWL_MAX_TID_COUNT ? 0 : tid);

	return 0;

drop_unlock_sta:
	iwl_trans_free_tx_cmd(mvm->trans, dev_cmd);
	spin_unlock(&mvmsta->lock);
drop:
	return -1;
}