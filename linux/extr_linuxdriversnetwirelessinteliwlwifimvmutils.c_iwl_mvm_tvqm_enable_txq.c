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
typedef  scalar_t__ u8 ;
struct iwl_tx_queue_cfg_cmd {scalar_t__ sta_id; scalar_t__ tid; int /*<<< orphan*/  flags; } ;
struct iwl_mvm {int /*<<< orphan*/ * hw_queue_to_mac80211; int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int,scalar_t__,...) ; 
 int IWL_DEFAULT_QUEUE_SIZE ; 
 scalar_t__ IWL_MAX_TID_COUNT ; 
 int IWL_MGMT_QUEUE_SIZE ; 
 scalar_t__ IWL_MGMT_TID ; 
 int /*<<< orphan*/  SCD_QUEUE_CFG ; 
 int /*<<< orphan*/  TX_QUEUE_CFG_ENABLE_QUEUE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int iwl_trans_txq_alloc (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,unsigned int) ; 

int iwl_mvm_tvqm_enable_txq(struct iwl_mvm *mvm, int mac80211_queue,
			    u8 sta_id, u8 tid, unsigned int timeout)
{
	struct iwl_tx_queue_cfg_cmd cmd = {
		.flags = cpu_to_le16(TX_QUEUE_CFG_ENABLE_QUEUE),
		.sta_id = sta_id,
		.tid = tid,
	};
	int queue, size = IWL_DEFAULT_QUEUE_SIZE;

	if (cmd.tid == IWL_MAX_TID_COUNT) {
		cmd.tid = IWL_MGMT_TID;
		size = IWL_MGMT_QUEUE_SIZE;
	}
	queue = iwl_trans_txq_alloc(mvm->trans, (void *)&cmd,
				    SCD_QUEUE_CFG, size, timeout);

	if (queue < 0) {
		IWL_DEBUG_TX_QUEUES(mvm,
				    "Failed allocating TXQ for sta %d tid %d, ret: %d\n",
				    sta_id, tid, queue);
		return queue;
	}

	IWL_DEBUG_TX_QUEUES(mvm, "Enabling TXQ #%d for sta %d tid %d\n",
			    queue, sta_id, tid);

	mvm->hw_queue_to_mac80211[queue] |= BIT(mac80211_queue);
	IWL_DEBUG_TX_QUEUES(mvm,
			    "Enabling TXQ #%d (mac80211 map:0x%x)\n",
			    queue, mvm->hw_queue_to_mac80211[queue]);

	return queue;
}