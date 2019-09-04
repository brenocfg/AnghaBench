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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct ieee80211_sta {int dummy; } ;
struct ath10k_pktlog_hdr {scalar_t__ payload; int /*<<< orphan*/  log_type; } ;
struct ath10k_per_peer_tx_stats {int /*<<< orphan*/  failed_pkts; int /*<<< orphan*/  retry_pkts; int /*<<< orphan*/  succ_pkts; int /*<<< orphan*/  flags; int /*<<< orphan*/  ratecode; void* failed_bytes; void* retry_bytes; void* succ_bytes; } ;
struct ath10k_peer {struct ieee80211_sta* sta; } ;
struct ath10k_10_2_peer_tx_stats {size_t tx_ppdu_cnt; size_t peer_id; int /*<<< orphan*/ * failed_pkts; int /*<<< orphan*/ * retry_pkts; int /*<<< orphan*/ * success_pkts; int /*<<< orphan*/ * flags; int /*<<< orphan*/ * ratecode; int /*<<< orphan*/ * failed_bytes; int /*<<< orphan*/ * retry_bytes; int /*<<< orphan*/ * success_bytes; } ;
struct ath10k {int /*<<< orphan*/  data_lock; struct ath10k_per_peer_tx_stats peer_tx_stats; } ;

/* Variables and functions */
 scalar_t__ ATH10K_10_2_TX_STATS_OFFSET ; 
 scalar_t__ ATH_PKTLOG_TYPE_TX_STAT ; 
 void* __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct ath10k_peer* ath10k_peer_find_by_id (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ath10k_update_per_peer_tx_stats (struct ath10k*,struct ieee80211_sta*,struct ath10k_per_peer_tx_stats*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,size_t) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_fetch_10_2_tx_stats(struct ath10k *ar, u8 *data)
{
	struct ath10k_pktlog_hdr *hdr = (struct ath10k_pktlog_hdr *)data;
	struct ath10k_per_peer_tx_stats *p_tx_stats = &ar->peer_tx_stats;
	struct ath10k_10_2_peer_tx_stats *tx_stats;
	struct ieee80211_sta *sta;
	struct ath10k_peer *peer;
	u16 log_type = __le16_to_cpu(hdr->log_type);
	u32 peer_id = 0, i;

	if (log_type != ATH_PKTLOG_TYPE_TX_STAT)
		return;

	tx_stats = (struct ath10k_10_2_peer_tx_stats *)((hdr->payload) +
		    ATH10K_10_2_TX_STATS_OFFSET);

	if (!tx_stats->tx_ppdu_cnt)
		return;

	peer_id = tx_stats->peer_id;

	rcu_read_lock();
	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, peer_id);
	if (!peer || !peer->sta) {
		ath10k_warn(ar, "Invalid peer id %d in peer stats buffer\n",
			    peer_id);
		goto out;
	}

	sta = peer->sta;
	for (i = 0; i < tx_stats->tx_ppdu_cnt; i++) {
		p_tx_stats->succ_bytes =
			__le16_to_cpu(tx_stats->success_bytes[i]);
		p_tx_stats->retry_bytes =
			__le16_to_cpu(tx_stats->retry_bytes[i]);
		p_tx_stats->failed_bytes =
			__le16_to_cpu(tx_stats->failed_bytes[i]);
		p_tx_stats->ratecode = tx_stats->ratecode[i];
		p_tx_stats->flags = tx_stats->flags[i];
		p_tx_stats->succ_pkts = tx_stats->success_pkts[i];
		p_tx_stats->retry_pkts = tx_stats->retry_pkts[i];
		p_tx_stats->failed_pkts = tx_stats->failed_pkts[i];

		ath10k_update_per_peer_tx_stats(ar, sta, p_tx_stats);
	}
	spin_unlock_bh(&ar->data_lock);
	rcu_read_unlock();

	return;

out:
	spin_unlock_bh(&ar->data_lock);
	rcu_read_unlock();
}