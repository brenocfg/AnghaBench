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
struct ath9k_htc_sta {scalar_t__* tid_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_lock; } ;
struct ath9k_htc_priv {TYPE_1__ tx; } ;

/* Variables and functions */
 scalar_t__ AGGR_STOP ; 
 size_t ATH9K_HTC_MAX_TID ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool __ath9k_htc_check_tx_aggr(struct ath9k_htc_priv *priv,
					     struct ath9k_htc_sta *ista, u8 tid)
{
	bool ret = false;

	spin_lock_bh(&priv->tx.tx_lock);
	if ((tid < ATH9K_HTC_MAX_TID) && (ista->tid_state[tid] == AGGR_STOP))
		ret = true;
	spin_unlock_bh(&priv->tx.tx_lock);

	return ret;
}