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
struct TYPE_4__ {int /*<<< orphan*/  vif; } ;
struct txq_info {TYPE_2__ txq; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; scalar_t__ in_reconfig; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* wake_tx_queue ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  trace_drv_wake_tx_queue (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct txq_info*) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void drv_wake_tx_queue(struct ieee80211_local *local,
				     struct txq_info *txq)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(txq->txq.vif);

	if (local->in_reconfig)
		return;

	if (!check_sdata_in_driver(sdata))
		return;

	trace_drv_wake_tx_queue(local, sdata, txq);
	local->ops->wake_tx_queue(&local->hw, &txq->txq);
}