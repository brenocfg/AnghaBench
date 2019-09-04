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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ tx_win_size; } ;
struct mwifiex_private {scalar_t__ bss_type; int /*<<< orphan*/  media_connected; TYPE_1__ add_ba_param; } ;
struct mwifiex_adapter {size_t priv_num; scalar_t__ coex_tx_win_size; scalar_t__ coex_win_size; struct mwifiex_private** priv; } ;

/* Variables and functions */
 size_t MAX_NUM_TID ; 
 scalar_t__ MWIFIEX_BSS_TYPE_P2P ; 
 scalar_t__ MWIFIEX_BSS_TYPE_STA ; 
 scalar_t__ MWIFIEX_BSS_TYPE_UAP ; 
 void* MWIFIEX_STA_AMPDU_DEF_TXWINSIZE ; 
 scalar_t__ MWIFIEX_UAP_AMPDU_DEF_TXWINSIZE ; 
 int /*<<< orphan*/  mwifiex_send_delba_txbastream_tbl (struct mwifiex_private*,size_t) ; 

void mwifiex_update_ampdu_txwinsize(struct mwifiex_adapter *adapter)
{
	u8 i;
	u32 tx_win_size;
	struct mwifiex_private *priv;

	for (i = 0; i < adapter->priv_num; i++) {
		if (!adapter->priv[i])
			continue;
		priv = adapter->priv[i];
		tx_win_size = priv->add_ba_param.tx_win_size;

		if (priv->bss_type == MWIFIEX_BSS_TYPE_STA)
			priv->add_ba_param.tx_win_size =
				MWIFIEX_STA_AMPDU_DEF_TXWINSIZE;

		if (priv->bss_type == MWIFIEX_BSS_TYPE_P2P)
			priv->add_ba_param.tx_win_size =
				MWIFIEX_STA_AMPDU_DEF_TXWINSIZE;

		if (priv->bss_type == MWIFIEX_BSS_TYPE_UAP)
			priv->add_ba_param.tx_win_size =
				MWIFIEX_UAP_AMPDU_DEF_TXWINSIZE;

		if (adapter->coex_win_size) {
			if (adapter->coex_tx_win_size)
				priv->add_ba_param.tx_win_size =
					adapter->coex_tx_win_size;
		}

		if (tx_win_size != priv->add_ba_param.tx_win_size) {
			if (!priv->media_connected)
				continue;
			for (i = 0; i < MAX_NUM_TID; i++)
				mwifiex_send_delba_txbastream_tbl(priv, i);
		}
	}
}