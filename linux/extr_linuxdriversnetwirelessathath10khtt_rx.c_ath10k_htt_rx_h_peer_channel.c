#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  info0; } ;
struct TYPE_6__ {int info0; } ;
struct TYPE_7__ {TYPE_2__ common; } ;
struct TYPE_5__ {int flags; } ;
struct htt_rx_desc {TYPE_4__ mpdu_start; TYPE_3__ msdu_end; TYPE_1__ attention; } ;
struct cfg80211_chan_def {struct ieee80211_channel* chan; } ;
struct ath10k_vif {int /*<<< orphan*/  vif; } ;
struct ath10k_peer {int /*<<< orphan*/  vdev_id; } ;
struct ath10k {int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_ATTENTION_FLAGS_PEER_IDX_INVALID ; 
 int /*<<< orphan*/  RX_MPDU_START_INFO0_PEER_IDX ; 
 int /*<<< orphan*/  RX_MSDU_END_INFO0_FIRST_MSDU ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ath10k_vif* ath10k_get_arvif (struct ath10k*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath10k_mac_vif_chan (int /*<<< orphan*/ ,struct cfg80211_chan_def*) ; 
 struct ath10k_peer* ath10k_peer_find_by_id (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ieee80211_channel *
ath10k_htt_rx_h_peer_channel(struct ath10k *ar, struct htt_rx_desc *rxd)
{
	struct ath10k_peer *peer;
	struct ath10k_vif *arvif;
	struct cfg80211_chan_def def;
	u16 peer_id;

	lockdep_assert_held(&ar->data_lock);

	if (!rxd)
		return NULL;

	if (rxd->attention.flags &
	    __cpu_to_le32(RX_ATTENTION_FLAGS_PEER_IDX_INVALID))
		return NULL;

	if (!(rxd->msdu_end.common.info0 &
	      __cpu_to_le32(RX_MSDU_END_INFO0_FIRST_MSDU)))
		return NULL;

	peer_id = MS(__le32_to_cpu(rxd->mpdu_start.info0),
		     RX_MPDU_START_INFO0_PEER_IDX);

	peer = ath10k_peer_find_by_id(ar, peer_id);
	if (!peer)
		return NULL;

	arvif = ath10k_get_arvif(ar, peer->vdev_id);
	if (WARN_ON_ONCE(!arvif))
		return NULL;

	if (ath10k_mac_vif_chan(arvif->vif, &def))
		return NULL;

	return def.chan;
}