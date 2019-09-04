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
struct mwl8k_priv {scalar_t__* txq_offset; scalar_t__ sram; TYPE_1__* txq; scalar_t__ ap_fw; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  txd_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int mwl8k_tx_queues (struct mwl8k_priv*) ; 
 int mwl8k_txq_init (struct ieee80211_hw*,int) ; 

__attribute__((used)) static int mwl8k_init_txqs(struct ieee80211_hw *hw)
{
	struct mwl8k_priv *priv = hw->priv;
	int rc = 0;
	int i;

	for (i = 0; i < mwl8k_tx_queues(priv); i++) {
		rc = mwl8k_txq_init(hw, i);
		if (rc)
			break;
		if (priv->ap_fw)
			iowrite32(priv->txq[i].txd_dma,
				  priv->sram + priv->txq_offset[i]);
	}
	return rc;
}