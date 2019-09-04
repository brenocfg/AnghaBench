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
typedef  scalar_t__ u32 ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_sta_vht_cap {int cap; } ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; } ;
struct TYPE_4__ {TYPE_1__* vdev_param; } ;
struct ath10k {int vht_cap_info; TYPE_2__ wmi; } ;
struct TYPE_3__ {scalar_t__ txbf; } ;

/* Variables and functions */
 int IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE ; 
 int IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE ; 
 int IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE ; 
 int IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WMI_TXBF_CONF_AFTER_ASSOC ; 
 scalar_t__ WMI_VDEV_PARAM_TXBF_MU_TX_BFEE ; 
 scalar_t__ WMI_VDEV_PARAM_TXBF_MU_TX_BFER ; 
 scalar_t__ WMI_VDEV_PARAM_TXBF_SU_TX_BFEE ; 
 scalar_t__ WMI_VDEV_PARAM_TXBF_SU_TX_BFER ; 
 scalar_t__ WMI_VDEV_PARAM_UNSUPPORTED ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,scalar_t__,int) ; 
 scalar_t__ ath10k_wmi_get_txbf_conf_scheme (struct ath10k*) ; 
 int ath10k_wmi_vdev_set_param (struct ath10k*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ath10k_mac_vif_recalc_txbf(struct ath10k *ar,
				      struct ieee80211_vif *vif,
				      struct ieee80211_sta_vht_cap vht_cap)
{
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	int ret;
	u32 param;
	u32 value;

	if (ath10k_wmi_get_txbf_conf_scheme(ar) != WMI_TXBF_CONF_AFTER_ASSOC)
		return 0;

	if (!(ar->vht_cap_info &
	      (IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
	       IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE |
	       IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
	       IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)))
		return 0;

	param = ar->wmi.vdev_param->txbf;
	value = 0;

	if (WARN_ON(param == WMI_VDEV_PARAM_UNSUPPORTED))
		return 0;

	/* The following logic is correct. If a remote STA advertises support
	 * for being a beamformer then we should enable us being a beamformee.
	 */

	if (ar->vht_cap_info &
	    (IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
	     IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE)) {
		if (vht_cap.cap & IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE)
			value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFEE;

		if (vht_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)
			value |= WMI_VDEV_PARAM_TXBF_MU_TX_BFEE;
	}

	if (ar->vht_cap_info &
	    (IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
	     IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)) {
		if (vht_cap.cap & IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE)
			value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFER;

		if (vht_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE)
			value |= WMI_VDEV_PARAM_TXBF_MU_TX_BFER;
	}

	if (value & WMI_VDEV_PARAM_TXBF_MU_TX_BFEE)
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFEE;

	if (value & WMI_VDEV_PARAM_TXBF_MU_TX_BFER)
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFER;

	ret = ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, param, value);
	if (ret) {
		ath10k_warn(ar, "failed to submit vdev param txbf 0x%x: %d\n",
			    value, ret);
		return ret;
	}

	return 0;
}