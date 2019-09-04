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
struct napi_struct {int dummy; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm_reorder_buffer {int /*<<< orphan*/  lock; } ;
struct iwl_mvm_baid_data {size_t sta_id; struct iwl_mvm_reorder_buffer* reorder_buf; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; int /*<<< orphan*/ * baid_map; } ;
struct iwl_frame_release {int baid; int /*<<< orphan*/  nssn; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_HT (struct iwl_mvm*,char*,int,int /*<<< orphan*/ ) ; 
 int IWL_RX_REORDER_DATA_INVALID_BAID ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_mvm_release_frames (struct iwl_mvm*,struct ieee80211_sta*,struct napi_struct*,struct iwl_mvm_baid_data*,struct iwl_mvm_reorder_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iwl_mvm_rx_frame_release(struct iwl_mvm *mvm, struct napi_struct *napi,
			      struct iwl_rx_cmd_buffer *rxb, int queue)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_frame_release *release = (void *)pkt->data;
	struct ieee80211_sta *sta;
	struct iwl_mvm_reorder_buffer *reorder_buf;
	struct iwl_mvm_baid_data *ba_data;

	int baid = release->baid;

	IWL_DEBUG_HT(mvm, "Frame release notification for BAID %u, NSSN %d\n",
		     release->baid, le16_to_cpu(release->nssn));

	if (WARN_ON_ONCE(baid == IWL_RX_REORDER_DATA_INVALID_BAID))
		return;

	rcu_read_lock();

	ba_data = rcu_dereference(mvm->baid_map[baid]);
	if (WARN_ON_ONCE(!ba_data))
		goto out;

	sta = rcu_dereference(mvm->fw_id_to_mac_id[ba_data->sta_id]);
	if (WARN_ON_ONCE(IS_ERR_OR_NULL(sta)))
		goto out;

	reorder_buf = &ba_data->reorder_buf[queue];

	spin_lock_bh(&reorder_buf->lock);
	iwl_mvm_release_frames(mvm, sta, napi, ba_data, reorder_buf,
			       le16_to_cpu(release->nssn));
	spin_unlock_bh(&reorder_buf->lock);

out:
	rcu_read_unlock();
}