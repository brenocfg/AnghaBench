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
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int dummy; } ;
struct ieee80211_hw {struct brcms_info* priv; } ;
struct brcms_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  wlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_wme_setparams (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_tx_queue_params const*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
brcms_ops_conf_tx(struct ieee80211_hw *hw, struct ieee80211_vif *vif, u16 queue,
		  const struct ieee80211_tx_queue_params *params)
{
	struct brcms_info *wl = hw->priv;

	spin_lock_bh(&wl->lock);
	brcms_c_wme_setparams(wl->wlc, queue, params, true);
	spin_unlock_bh(&wl->lock);

	return 0;
}