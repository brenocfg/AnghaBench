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
typedef  int /*<<< orphan*/  u16 ;
struct htt_rx_addba {int /*<<< orphan*/  window_size; int /*<<< orphan*/  info0; } ;
struct htt_resp {struct htt_rx_addba rx_addba; } ;
struct ath10k_vif {int /*<<< orphan*/  vif; } ;
struct ath10k_peer {int /*<<< orphan*/  addr; int /*<<< orphan*/  vdev_id; } ;
struct ath10k {int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 int /*<<< orphan*/  HTT_RX_BA_INFO0_PEER_ID ; 
 int /*<<< orphan*/  HTT_RX_BA_INFO0_TID ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath10k_vif* ath10k_get_arvif (struct ath10k*,int /*<<< orphan*/ ) ; 
 struct ath10k_peer* ath10k_peer_find_by_id (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_start_rx_ba_session_offl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_htt_rx_addba(struct ath10k *ar, struct htt_resp *resp)
{
	struct htt_rx_addba *ev = &resp->rx_addba;
	struct ath10k_peer *peer;
	struct ath10k_vif *arvif;
	u16 info0, tid, peer_id;

	info0 = __le16_to_cpu(ev->info0);
	tid = MS(info0, HTT_RX_BA_INFO0_TID);
	peer_id = MS(info0, HTT_RX_BA_INFO0_PEER_ID);

	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt rx addba tid %hu peer_id %hu size %hhu\n",
		   tid, peer_id, ev->window_size);

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, peer_id);
	if (!peer) {
		ath10k_warn(ar, "received addba event for invalid peer_id: %hu\n",
			    peer_id);
		spin_unlock_bh(&ar->data_lock);
		return;
	}

	arvif = ath10k_get_arvif(ar, peer->vdev_id);
	if (!arvif) {
		ath10k_warn(ar, "received addba event for invalid vdev_id: %u\n",
			    peer->vdev_id);
		spin_unlock_bh(&ar->data_lock);
		return;
	}

	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt rx start rx ba session sta %pM tid %hu size %hhu\n",
		   peer->addr, tid, ev->window_size);

	ieee80211_start_rx_ba_session_offl(arvif->vif, peer->addr, tid);
	spin_unlock_bh(&ar->data_lock);
}