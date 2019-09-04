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
struct ieee80211_hw {struct ath10k* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  width; TYPE_1__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_2__ def; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  data_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_chanctx_conf*) ; 
 int /*<<< orphan*/  ath10k_mac_update_rx_channel (struct ath10k*,struct ieee80211_chanctx_conf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_monitor_recalc (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_recalc_radar_detection (struct ath10k*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath10k_mac_op_add_chanctx(struct ieee80211_hw *hw,
			  struct ieee80211_chanctx_conf *ctx)
{
	struct ath10k *ar = hw->priv;

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx add freq %hu width %d ptr %pK\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx);

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	ath10k_mac_update_rx_channel(ar, ctx, NULL, 0);
	spin_unlock_bh(&ar->data_lock);

	ath10k_recalc_radar_detection(ar);
	ath10k_monitor_recalc(ar);

	mutex_unlock(&ar->conf_mutex);

	return 0;
}