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
typedef  int u32 ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct TYPE_4__ {TYPE_1__* vdev_param; } ;
struct ath10k {int vht_cap_info; TYPE_2__ wmi; } ;
struct TYPE_3__ {int /*<<< orphan*/  txbf; } ;

/* Variables and functions */
 int IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE ; 
 int IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE ; 
 int IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE ; 
 int IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_BF_SOUND_DIM_OFFSET ; 
 scalar_t__ WMI_TXBF_CONF_BEFORE_ASSOC ; 
 int /*<<< orphan*/  WMI_TXBF_STS_CAP_OFFSET ; 
 int WMI_VDEV_PARAM_TXBF_MU_TX_BFEE ; 
 int WMI_VDEV_PARAM_TXBF_MU_TX_BFER ; 
 int WMI_VDEV_PARAM_TXBF_SU_TX_BFEE ; 
 int WMI_VDEV_PARAM_TXBF_SU_TX_BFER ; 
 int ath10k_mac_get_vht_cap_bf_sound_dim (struct ath10k*) ; 
 int ath10k_mac_get_vht_cap_bf_sts (struct ath10k*) ; 
 scalar_t__ ath10k_wmi_get_txbf_conf_scheme (struct ath10k*) ; 
 int ath10k_wmi_vdev_set_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath10k_mac_set_txbf_conf(struct ath10k_vif *arvif)
{
	u32 value = 0;
	struct ath10k *ar = arvif->ar;
	int nsts;
	int sound_dim;

	if (ath10k_wmi_get_txbf_conf_scheme(ar) != WMI_TXBF_CONF_BEFORE_ASSOC)
		return 0;

	nsts = ath10k_mac_get_vht_cap_bf_sts(ar);
	if (ar->vht_cap_info & (IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
				IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE))
		value |= SM(nsts, WMI_TXBF_STS_CAP_OFFSET);

	sound_dim = ath10k_mac_get_vht_cap_bf_sound_dim(ar);
	if (ar->vht_cap_info & (IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
				IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE))
		value |= SM(sound_dim, WMI_BF_SOUND_DIM_OFFSET);

	if (!value)
		return 0;

	if (ar->vht_cap_info & IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE)
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFER;

	if (ar->vht_cap_info & IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)
		value |= (WMI_VDEV_PARAM_TXBF_MU_TX_BFER |
			  WMI_VDEV_PARAM_TXBF_SU_TX_BFER);

	if (ar->vht_cap_info & IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE)
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFEE;

	if (ar->vht_cap_info & IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE)
		value |= (WMI_VDEV_PARAM_TXBF_MU_TX_BFEE |
			  WMI_VDEV_PARAM_TXBF_SU_TX_BFEE);

	return ath10k_wmi_vdev_set_param(ar, arvif->vdev_id,
					 ar->wmi.vdev_param->txbf, value);
}