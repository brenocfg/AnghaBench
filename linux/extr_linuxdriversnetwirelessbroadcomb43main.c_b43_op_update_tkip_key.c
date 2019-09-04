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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/ * addr; } ;
struct ieee80211_key_conf {int hw_key_idx; } ;
struct ieee80211_hw {int dummy; } ;
struct b43_wldev {int dummy; } ;
struct b43_wl {struct b43_wldev* current_dev; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ B43_STAT_INITIALIZED ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  keymac_write (struct b43_wldev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modparam_hwtkip ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_tkip_phase1_write (struct b43_wldev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43_op_update_tkip_key(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_key_conf *keyconf,
				   struct ieee80211_sta *sta,
				   u32 iv32, u16 *phase1key)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);
	struct b43_wldev *dev;
	int index = keyconf->hw_key_idx;

	if (B43_WARN_ON(!modparam_hwtkip))
		return;

	/* This is only called from the RX path through mac80211, where
	 * our mutex is already locked. */
	B43_WARN_ON(!mutex_is_locked(&wl->mutex));
	dev = wl->current_dev;
	B43_WARN_ON(!dev || b43_status(dev) < B43_STAT_INITIALIZED);

	keymac_write(dev, index, NULL);	/* First zero out mac to avoid race */

	rx_tkip_phase1_write(dev, index, iv32, phase1key);
	/* only pairwise TKIP keys are supported right now */
	if (WARN_ON(!sta))
		return;
	keymac_write(dev, index, sta->addr);
}