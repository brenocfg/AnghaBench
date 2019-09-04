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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath5k_hw {TYPE_1__* txqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  txq_max; } ;

/* Variables and functions */
 size_t AR5K_TX_QUEUE_ID_DATA_MIN ; 
 int /*<<< orphan*/  ATH5K_TXQ_LEN_MAX ; 
 int /*<<< orphan*/  ATH_RXBUF ; 

__attribute__((used)) static void ath5k_get_ringparam(struct ieee80211_hw *hw,
				u32 *tx, u32 *tx_max, u32 *rx, u32 *rx_max)
{
	struct ath5k_hw *ah = hw->priv;

	*tx = ah->txqs[AR5K_TX_QUEUE_ID_DATA_MIN].txq_max;

	*tx_max = ATH5K_TXQ_LEN_MAX;
	*rx = *rx_max = ATH_RXBUF;
}