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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ uapsd; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; TYPE_2__ u; struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_STA_PS_PARAM_TX_WAKE_THRESHOLD ; 
 int /*<<< orphan*/  WMI_STA_PS_TX_WAKE_THRESHOLD_ALWAYS ; 
 int /*<<< orphan*/  WMI_STA_PS_TX_WAKE_THRESHOLD_NEVER ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_set_sta_ps_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_mac_vif_recalc_ps_wake_threshold(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;
	u32 param;
	u32 value;
	int ret;

	lockdep_assert_held(&arvif->ar->conf_mutex);

	if (arvif->u.sta.uapsd)
		value = WMI_STA_PS_TX_WAKE_THRESHOLD_NEVER;
	else
		value = WMI_STA_PS_TX_WAKE_THRESHOLD_ALWAYS;

	param = WMI_STA_PS_PARAM_TX_WAKE_THRESHOLD;
	ret = ath10k_wmi_set_sta_ps_param(ar, arvif->vdev_id, param, value);
	if (ret) {
		ath10k_warn(ar, "failed to submit ps wake threshold %u on vdev %i: %d\n",
			    value, arvif->vdev_id, ret);
		return ret;
	}

	return 0;
}