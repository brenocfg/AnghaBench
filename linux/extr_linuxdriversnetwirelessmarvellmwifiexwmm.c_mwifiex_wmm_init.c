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
struct TYPE_4__ {int /*<<< orphan*/  highest_queued_prio; int /*<<< orphan*/  tx_pkts_queued; int /*<<< orphan*/  drv_pkt_delay_max; } ;
struct mwifiex_private {TYPE_2__ wmm; TYPE_1__* aggr_prio_tbl; void** tos_to_tid_inv; } ;
struct mwifiex_adapter {int priv_num; scalar_t__ tx_buf_size; struct mwifiex_private** priv; } ;
struct TYPE_3__ {void* ampdu_user; void* ampdu_ap; void* amsdu; } ;

/* Variables and functions */
 void* BA_STREAM_NOT_ALLOWED ; 
 int /*<<< orphan*/  HIGH_PRIO_TID ; 
 int MAX_NUM_TID ; 
 scalar_t__ MWIFIEX_TX_DATA_BUF_SIZE_2K ; 
 int /*<<< orphan*/  MWIFIEX_WMM_DRV_DELAY_MAX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_tx_amsdu ; 
 int /*<<< orphan*/  mwifiex_reset_11n_rx_seq_num (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_set_ba_params (struct mwifiex_private*) ; 

void
mwifiex_wmm_init(struct mwifiex_adapter *adapter)
{
	int i, j;
	struct mwifiex_private *priv;

	for (j = 0; j < adapter->priv_num; ++j) {
		priv = adapter->priv[j];
		if (!priv)
			continue;

		for (i = 0; i < MAX_NUM_TID; ++i) {
			if (!disable_tx_amsdu &&
			    adapter->tx_buf_size > MWIFIEX_TX_DATA_BUF_SIZE_2K)
				priv->aggr_prio_tbl[i].amsdu =
							priv->tos_to_tid_inv[i];
			else
				priv->aggr_prio_tbl[i].amsdu =
							BA_STREAM_NOT_ALLOWED;
			priv->aggr_prio_tbl[i].ampdu_ap =
							priv->tos_to_tid_inv[i];
			priv->aggr_prio_tbl[i].ampdu_user =
							priv->tos_to_tid_inv[i];
		}

		priv->aggr_prio_tbl[6].amsdu
					= priv->aggr_prio_tbl[6].ampdu_ap
					= priv->aggr_prio_tbl[6].ampdu_user
					= BA_STREAM_NOT_ALLOWED;

		priv->aggr_prio_tbl[7].amsdu = priv->aggr_prio_tbl[7].ampdu_ap
					= priv->aggr_prio_tbl[7].ampdu_user
					= BA_STREAM_NOT_ALLOWED;

		mwifiex_set_ba_params(priv);
		mwifiex_reset_11n_rx_seq_num(priv);

		priv->wmm.drv_pkt_delay_max = MWIFIEX_WMM_DRV_DELAY_MAX;
		atomic_set(&priv->wmm.tx_pkts_queued, 0);
		atomic_set(&priv->wmm.highest_queued_prio, HIGH_PRIO_TID);
	}
}