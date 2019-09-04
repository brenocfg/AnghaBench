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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
struct cfg80211_chan_def {TYPE_1__* chan; } ;
struct cfg80211_bitrate_mask {TYPE_2__* control; } ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; struct cfg80211_bitrate_mask bitrate_mask; struct ath10k* ar; } ;
struct ath10k {int ht_cap_info; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  hw; int /*<<< orphan*/  num_rf_chains; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_4__ {scalar_t__* ht_mcs; scalar_t__ gi; int /*<<< orphan*/ * vht_mcs; } ;
struct TYPE_3__ {int band; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ NL80211_TXRATE_FORCE_LGI ; 
 scalar_t__ WMI_FIXED_RATE_NONE ; 
 int WMI_HT_CAP_LDPC ; 
 scalar_t__ ath10k_mac_bitrate_mask_get_single_nss (struct ath10k*,int,struct cfg80211_bitrate_mask const*,int*) ; 
 int ath10k_mac_bitrate_mask_get_single_rate (struct ath10k*,int,struct cfg80211_bitrate_mask const*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ ath10k_mac_bitrate_mask_has_single_rate (struct ath10k*,int,struct cfg80211_bitrate_mask const*) ; 
 int /*<<< orphan*/  ath10k_mac_can_set_bitrate_mask (struct ath10k*,int,struct cfg80211_bitrate_mask const*) ; 
 int /*<<< orphan*/  ath10k_mac_max_ht_nss (scalar_t__ const*) ; 
 int /*<<< orphan*/  ath10k_mac_max_vht_nss (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ath10k_mac_set_bitrate_mask_iter ; 
 int ath10k_mac_set_fixed_rate_params (struct ath10k_vif*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ ath10k_mac_vif_chan (struct ieee80211_vif*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_iterate_stations_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath10k_vif*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_mac_op_set_bitrate_mask(struct ieee80211_hw *hw,
					  struct ieee80211_vif *vif,
					  const struct cfg80211_bitrate_mask *mask)
{
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	struct cfg80211_chan_def def;
	struct ath10k *ar = arvif->ar;
	enum nl80211_band band;
	const u8 *ht_mcs_mask;
	const u16 *vht_mcs_mask;
	u8 rate;
	u8 nss;
	u8 sgi;
	u8 ldpc;
	int single_nss;
	int ret;

	if (ath10k_mac_vif_chan(vif, &def))
		return -EPERM;

	band = def.chan->band;
	ht_mcs_mask = mask->control[band].ht_mcs;
	vht_mcs_mask = mask->control[band].vht_mcs;
	ldpc = !!(ar->ht_cap_info & WMI_HT_CAP_LDPC);

	sgi = mask->control[band].gi;
	if (sgi == NL80211_TXRATE_FORCE_LGI)
		return -EINVAL;

	if (ath10k_mac_bitrate_mask_has_single_rate(ar, band, mask)) {
		ret = ath10k_mac_bitrate_mask_get_single_rate(ar, band, mask,
							      &rate, &nss);
		if (ret) {
			ath10k_warn(ar, "failed to get single rate for vdev %i: %d\n",
				    arvif->vdev_id, ret);
			return ret;
		}
	} else if (ath10k_mac_bitrate_mask_get_single_nss(ar, band, mask,
							  &single_nss)) {
		rate = WMI_FIXED_RATE_NONE;
		nss = single_nss;
	} else {
		rate = WMI_FIXED_RATE_NONE;
		nss = min(ar->num_rf_chains,
			  max(ath10k_mac_max_ht_nss(ht_mcs_mask),
			      ath10k_mac_max_vht_nss(vht_mcs_mask)));

		if (!ath10k_mac_can_set_bitrate_mask(ar, band, mask))
			return -EINVAL;

		mutex_lock(&ar->conf_mutex);

		arvif->bitrate_mask = *mask;
		ieee80211_iterate_stations_atomic(ar->hw,
						  ath10k_mac_set_bitrate_mask_iter,
						  arvif);

		mutex_unlock(&ar->conf_mutex);
	}

	mutex_lock(&ar->conf_mutex);

	ret = ath10k_mac_set_fixed_rate_params(arvif, rate, nss, sgi, ldpc);
	if (ret) {
		ath10k_warn(ar, "failed to set fixed rate params on vdev %i: %d\n",
			    arvif->vdev_id, ret);
		goto exit;
	}

exit:
	mutex_unlock(&ar->conf_mutex);

	return ret;
}