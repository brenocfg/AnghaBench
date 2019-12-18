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
struct txq_info {int /*<<< orphan*/  txq; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv_wake_tx_queue (struct ieee80211_local*,struct txq_info*) ; 
 int /*<<< orphan*/  ieee80211_schedule_txq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void schedule_and_wake_txq(struct ieee80211_local *local,
					 struct txq_info *txqi)
{
	ieee80211_schedule_txq(&local->hw, &txqi->txq);
	drv_wake_tx_queue(local, txqi);
}