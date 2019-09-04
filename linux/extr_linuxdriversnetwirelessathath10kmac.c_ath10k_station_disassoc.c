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
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; int /*<<< orphan*/  wme; } ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  num_legacy_stations; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int ath10k_clear_peer_keys (struct ath10k_vif*,int /*<<< orphan*/ ) ; 
 int ath10k_recalc_rtscts_prot (struct ath10k_vif*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_station_disassoc(struct ath10k *ar,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta)
{
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	if (!sta->wme) {
		arvif->num_legacy_stations--;
		ret = ath10k_recalc_rtscts_prot(arvif);
		if (ret) {
			ath10k_warn(ar, "failed to recalculate rts/cts prot for vdev %d: %d\n",
				    arvif->vdev_id, ret);
			return ret;
		}
	}

	ret = ath10k_clear_peer_keys(arvif, sta->addr);
	if (ret) {
		ath10k_warn(ar, "failed to clear all peer wep keys for vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	return ret;
}