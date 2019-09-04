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
typedef  size_t u8 ;
struct iwl_mvm {int* hw_queue_to_mac80211; int /*<<< orphan*/  queue_info_lock; TYPE_1__* queue_info; } ;
struct TYPE_2__ {int tid_bitmap; scalar_t__ hw_queue_refcount; size_t ra_sta_id; size_t txq_tid; int /*<<< orphan*/  mac80211_ac; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  IEEE80211_AC_VO ; 
 int IEEE80211_INVAL_HW_QUEUE ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int,size_t) ; 
 size_t IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/  WARN (int,char*,int,int,size_t,size_t) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tid_to_mac80211_ac ; 

__attribute__((used)) static bool iwl_mvm_update_txq_mapping(struct iwl_mvm *mvm, int queue,
				       int mac80211_queue, u8 sta_id, u8 tid)
{
	bool enable_queue = true;

	spin_lock_bh(&mvm->queue_info_lock);

	/* Make sure this TID isn't already enabled */
	if (mvm->queue_info[queue].tid_bitmap & BIT(tid)) {
		spin_unlock_bh(&mvm->queue_info_lock);
		IWL_ERR(mvm, "Trying to enable TXQ %d with existing TID %d\n",
			queue, tid);
		return false;
	}

	/* Update mappings and refcounts */
	if (mvm->queue_info[queue].hw_queue_refcount > 0)
		enable_queue = false;

	if (mac80211_queue != IEEE80211_INVAL_HW_QUEUE) {
		WARN(mac80211_queue >=
		     BITS_PER_BYTE * sizeof(mvm->hw_queue_to_mac80211[0]),
		     "cannot track mac80211 queue %d (queue %d, sta %d, tid %d)\n",
		     mac80211_queue, queue, sta_id, tid);
		mvm->hw_queue_to_mac80211[queue] |= BIT(mac80211_queue);
	}

	mvm->queue_info[queue].hw_queue_refcount++;
	mvm->queue_info[queue].tid_bitmap |= BIT(tid);
	mvm->queue_info[queue].ra_sta_id = sta_id;

	if (enable_queue) {
		if (tid != IWL_MAX_TID_COUNT)
			mvm->queue_info[queue].mac80211_ac =
				tid_to_mac80211_ac[tid];
		else
			mvm->queue_info[queue].mac80211_ac = IEEE80211_AC_VO;

		mvm->queue_info[queue].txq_tid = tid;
	}

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Enabling TXQ #%d refcount=%d (mac80211 map:0x%x)\n",
			    queue, mvm->queue_info[queue].hw_queue_refcount,
			    mvm->hw_queue_to_mac80211[queue]);

	spin_unlock_bh(&mvm->queue_info_lock);

	return enable_queue;
}